#include "stadfx.h"


// �����ڵ��������Ĭ�Ϲ���Ϊ�������ӽڵ����
class CreateModelToSaveVisitor :public osg::NodeVisitor
{
public:
	CreateModelToSaveVisitor() :osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		_group = new osg::Group;
		_addToModel = false;
	}

	// ���ʸ������͵Ľڵ�
	virtual void apply(osg::Node& node)
	{
		// ����ģ�ͽڵ������������Ƭ
		osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*>(&node);
		if (scribe)
		{
			for (unsigned int i = 0; i < scribe->getNumChildren();i++)
			{
				_group->addChild(scribe->getChild(i));
			}
		}

		else
		{
			// ����һ����Ҫ���ʵĽڵ��ƽ�
			traverse(node);
		}
	}
	osg::ref_ptr<osg::Group> _group;
	bool _addToModel;
};


typedef std::vector<osg::ref_ptr<osgFX::Scribe>> SelectedNodes; // ѡ�нڵ�
// ɾ���ڵ������
class DeleteSelectedNodesVisitor :public osg::NodeVisitor
{
	DeleteSelectedNodesVisitor() :osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{

	}

	virtual void apply(osg::Node& node)
	{
		osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*>(&node);
		if (scribe)
		{
			_selectedNodes.push_back(scribe);
		}
		else
		{
			traverse(node);
		}
	}

	// �޼�ѡ�еĽڵ�
	void pruneSelectedNodes()
	{
		auto it = _selectedNodes.begin();
		for (; it != _selectedNodes.end(); it++)
		{
			osg::Node* node = it->get();

			// vector���͵ĸ��ڵ��б�
			osg::Node::ParentList parents = node->getParents();
			auto itParents = parents.cbegin();
			for (; itParents != parents.cend(); itParents++)
			{
				// ÿһ�����ڵ㶼�Ƴ��������
				(*itParents)->removeChild(node);
			}
		}
	}

	SelectedNodes _selectedNodes;
};

// ����¼�����
class PickHandler :public osgGA::GUIEventHandler
{
public:
	PickHandler():
		_mx(0.0),_my(0.0),
		_usePolytopeIntersector(false),
		_useWindowCoordinates(false),
		_precisionHint(osgUtil::Intersector::USE_DOUBLE_CALCULATIONS), // �ڲ��������ʹ�õľ���
		_primitiveMask(osgUtil::PolytopeIntersector::ALL_PRIMITIVES) // ָ��Ҫ���Ļ������ͣ��˴�Ϊ���У���Ϊ�ཻ�ĵ㡢�ߡ���
	{

	}
	~PickHandler()
	{

	}

	void setPrimitiveMask(unsigned int primitiveMask)
	{
		_primitiveMask = primitiveMask;
	}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*> (&aa);
		if (!viewer)
			return false;

		switch (ea.getEventType())
		{
		// ������
		case osgGA::GUIEventAdapter::KEYUP:
		{
			if (ea.getKey() == 's')
			{
				saveSelectedModel(viewer->getSceneData());
			}

			else if (ea.getKey() == 'o')
			{
				osg::notify(osg::NOTICE) << "Saved model tofile 'saved_model.osgt'" << std::endl;
				osgDB::writeNodeFile(*(viewer->getSceneData()),"save_model.osgt");
			}
		}

		// ����
		case osgGA::GUIEventAdapter::PUSH:
		
		// ����ƶ���
		case osgGA::GUIEventAdapter::MOVE:
		{
			_mx = ea.getX();
			_my = ea.getY();
			return false;
		}

		// ��갴���ͷ�
		case osgGA::GUIEventAdapter::RELEASE:
		{
			if (_mx == ea.getX() && _my == ea.getY())
			{
				pick(ea, viewer);
			}
			return true;
		}
		default:
			return false;
		}
	}
	void fullWindowIntersectionTest(osgViewer::Viewer* viewer)
	{
		osg::ref_ptr<osgUtil::IntersectorGroup> intersectors = new osgUtil::IntersectorGroup;

		osg::Viewport* viewport = viewer->getCamera()->getViewport();
		unsigned  int numX = 100;
		unsigned  int numY = 100;

		double dx = viewport->width() / double(numX - 1);
		double dy = viewport->width() / double(numY - 1);
		
		double y = viewport->x();
		for (unsigned int r = 0; r < numY; r++)
		{
			double x = viewport->x();
			for (unsigned int c = 0; c < numX; c++)
			{
				osg::ref_ptr<osgUtil::Intersector> intersector;
				if (_usePolytopeIntersector)
				{
					osg::ref_ptr<osgUtil::PolytopeIntersector> pi = new osgUtil::PolytopeIntersector(osgUtil::Intersector::WINDOW, x - dx * 0.5, y - dy * 0.5, x + dx * 0.5, y + dy * 0.5);
					pi->setPrimitiveMask(_primitiveMask);
					intersector = pi.get();
				}
				else
				{
					intersector = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);
				}

				intersector->setPrecisionHint(_precisionHint);
				intersectors->getIntersectors().push_back(intersector);
				x += dx;
			}
			y += dy;
		}
		osgUtil::IntersectionVisitor iv(intersectors.get());

		osg::ElapsedTime elapsedTime;
		viewer->getCamera()->accept(iv);

		OSG_NOTICE << "Intersection traversal took " << elapsedTime.elapsedTime_m() << "ms for " << intersectors->getIntersectors().size() << " intersectors" << std::endl;
	}
	void pick(const osgGA::GUIEventAdapter& ea, osgViewer::Viewer* viewer)
	{
		osg::Node* scene = viewer->getSceneData();
		if (!scene) return;

		osg::notify(osg::NOTICE) << std::endl;

		osg::Node* node = NULL;
		osg::Group* parent = NULL;

		if (_usePolytopeIntersector)
		{
			osgUtil::PolytopeIntersector* picker;
			if (_useWindowCoordinates)
			{
				osg::Viewport* viewport = viewer->getCamera()->getViewport();
				double mx = viewport->x() + (int)((double)viewport->width() * (ea.getXnormalized() * 0.5 + 0.5));
				double my = viewport->y() + (int)((double)viewport->height() * (ea.getYnormalized() * 0.5 + 0.5));

				double w = 5.0f;
				double h = 5.0f;
				picker = new osgUtil::PolytopeIntersector(osgUtil::Intersector::WINDOW, mx - w, my - h, mx + w, my + h);
			}

			else
			{
				double mx = ea.getXnormalized();
				double my = ea.getYnormalized();
				double w = 0.05;
				double h = 0.05;
				picker = new osgUtil::PolytopeIntersector(osgUtil::Intersector::PROJECTION, mx - w, my - h, mx + w, my + h);
			}

			picker->setPrecisionHint(_precisionHint);
			picker->setPrimitiveMask(_primitiveMask);

			osgUtil::IntersectionVisitor iv(picker);
			osg::ElapsedTime elapsedTime;
			viewer->getCamera()->accept(iv);

			OSG_NOTICE << "PoltyopeIntersector traversal took " << elapsedTime.elapsedTime_m() << "ms" << std::endl;
			if (picker->containsIntersections())
			{
				osgUtil::PolytopeIntersector::Intersection intersection = picker->getFirstIntersection();
				OSG_NOTICE << "Picked " << intersection.localIntersectionPoint << std::endl
					<< "  Distance to ref. plane " << intersection.distance
					<< "  max, dist " << intersection.maxDistance
					<< " primitive index " << intersection.primitiveIndex
					<< " numIntersecitonPoints "
					<< intersection.numIntersectionPoints
					<< std::endl;

				osg::NodePath& nodePath = intersection.nodePath;
				node = (nodePath.size() >= 1) ? nodePath[nodePath.size() - 1] : 0;
				parent = (nodePath.size() >= 2) ? dynamic_cast<osg::Group*>(nodePath[nodePath.size() - 2]) : 0;

				if (node)
					std::cout << "  Hits" << node->className() << "  node path size " << nodePath.size() << std::endl;
				toggleScribe(parent, node);
			}
		}
		else
		{
			osgUtil::LineSegmentIntersector* picker;
			if (!_useWindowCoordinates)
			{
				picker = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
			}
			else
			{
				osg::Viewport* viewport = viewer->getCamera()->getViewport();
				float mx = viewport->x() + (int)((double)viewport->width() * (ea.getXnormalized() * 0.5 + 0.5));
				float my = viewport->y() + (int)((double)viewport->height() * (ea.getYnormalized() * 0.5 + 0.5));
				picker = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, mx, my);
			}
			picker->setPrecisionHint(_precisionHint);

			osgUtil::IntersectionVisitor iv(picker);
			osg::ElapsedTime elapsedTime;
			viewer->getCamera()->accept(iv);
			OSG_NOTICE << "LineSegmentIntersector traversal took " << elapsedTime.elapsedTime_m() << "ms" << std::endl;
			if (picker->containsIntersections())
			{
				osgUtil::LineSegmentIntersector::Intersection intersection = picker->getFirstIntersection(); // ��һ���ཻ
				OSG_NOTICE << "Picked " << intersection.getLocalIntersectPoint() << std::endl
					<< "  primitive index " << intersection.primitiveIndex
					<< std::endl;

				osg::NodePath& path = intersection.nodePath;
				node = (path.size() >= 1) ? path[path.size() - 1] : 0;
				parent = (path.size() >= 2) ? dynamic_cast<osg::Group*>(path[path.size() - 2]) : 0;

				if (node)
					std::cout << " Hits " << node->className() << " nodePath size" << path.size() << std::endl;
				toggleScribe(parent, node);
			}
		}
	}
	void toggleScribe(osg::Group* parent, osg::Node* node)
	{
		if (!parent || !node)
		{
			return;
		}

		std::cout << "  parent " << parent->className() << std::endl;

		osgFX::Scribe* parentAsScribe = dynamic_cast<osgFX::Scribe*>(parent);
		if (!parentAsScribe)
		{
			osgFX::Scribe* scribe = new osgFX::Scribe();
			scribe->addChild(node);
			parent->replaceChild(node, scribe);
		}
		else
		{
			osg::Node::ParentList parentList = parentAsScribe->getParents();
			for (osg::Node::ParentList::iterator it = parentList.begin(); it != parentList.end();it++)
			{
				(*it)->replaceChild(parentAsScribe, node);
			}
		}
	}
	void saveSelectedModel(osg::Node* scene)
	{
		if (!scene)
			return;

		CreateModelToSaveVisitor cmtsv;
		scene->accept(cmtsv);

		if (cmtsv._group->getNumChildren() > 0)
		{
			std::cout << "Writing selected components to 'selected_model.osgt'" << std::endl;
			osgDB::writeNodeFile(*cmtsv._group, "selected_model.osgt");
		}
	}

	void setPrecisionHint(osgUtil::Intersector::PrecisionHint hind)
	{
		_precisionHint = hind;
	}
protected:
	float _mx;
	float _my;
	bool _usePolytopeIntersector;
	bool _useWindowCoordinates;


	// �����࣬�ཻ����
	osgUtil::Intersector::PrecisionHint _precisionHint;
	unsigned int _primitiveMask;
};

class ConvertPrimitives :public osg::NodeVisitor
{
public:
	osg::PrimitiveSet::Mode _mode;

	ConvertPrimitives(osg::PrimitiveSet::Mode mode) :
		osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
		_mode(mode)
	{

	}

	void apply(osg::Geometry& geometry)
	{
		if (!geometry.getVertexArray())
			return;
		unsigned int numVertices = geometry.getVertexArray()->getNumElements();

		if (_mode == osg::PrimitiveSet::POINTS)
		{
			geometry.removePrimitiveSet(0, geometry.getNumPrimitiveSets());
			geometry.addPrimitiveSet(new osg::DrawArrays(_mode, 0, numVertices));
		}

		else if (_mode == osg::PrimitiveSet::LINES)
		{
			geometry.removePrimitiveSet(0, geometry.getNumPrimitiveSets());
			geometry.addPrimitiveSet(new osg::DrawArrays(_mode, 0, numVertices));
		}
	}
};

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);

	osgViewer::Viewer(arguments);

}
