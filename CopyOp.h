#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/Texture>
#include <osg/StateSet>
#include <osg/StateAttribute>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <iostream>

class MyCopyOp :public osg::CopyOp
{
public:
	// �Զ���Copy�࣬�������������Ϣ
	inline MyCopyOp(CopyFlags flags = SHALLOW_COPY) :
		osg::CopyOp(flags), _blank(2), _number(5)
	{

	}

	// �����������ڿ��������Ϣ��ʽ��ʵ�������ǹ������
	inline void moveIn()const
	{
		_blank += _number;
	}

	inline void moveOut() const
	{
		_blank -= _number;
	}

	inline void writeIndent() const
	{
		for (int i = 0; i < _blank; i++)
		{
			std::cout << " ";
		}
	}

	// ���ü�����copy
	virtual osg::Referenced* operator()(const osg::Referenced* ref)const
	{
		writeIndent();
		std::cout << "copying Referenced" << ref << '\n';
		moveIn();
		osg::Referenced* ret_ref = CopyOp::operator()(ref);
		moveOut();
		return ret_ref;
	}
	// ����copy
	virtual osg::Object* operator()(const osg::Object* obj)const
	{
		writeIndent();
		std::cout << "copying Object" << obj;
		if (obj)
		{
			std::cout << " " << obj->className();
		}
		std::cout << '\n';
		moveIn();
		osg::Object* ret_obj = CopyOp::operator()(obj);
		moveOut();
		return ret_obj;
	}

	// �ڵ�copy
	virtual osg::Node* operator()(const osg::Node* node)const
	{
		writeIndent();
		std::cout << "copying node" << node;

		if (node)
		{
			std::cout << " " << node->className() << " " << node->getName() << "";
		}

		std::cout << std::endl;
		moveIn();
		osg::Node* ret_node = CopyOp::operator()(node);
		moveOut();
		return ret_node;
	}

	virtual osg::Drawable* operator()(const osg::Drawable* drawable)const
	{
		writeIndent();
		std::cout << "copying Drawable" << drawable;

		if (drawable)
		{
			std::cout << "copying Drawable" << drawable;
		}

		std::cout << std::endl;
		moveIn();
		osg::Drawable* ret_drawable = CopyOp::operator()(drawable);
		moveOut();
		return ret_drawable;
	}

	// ״̬��
	virtual osg::StateSet* operator()(const osg::StateSet* stateSet)const
	{
		writeIndent();
		std::cout << "Copying StateSet" << stateSet;
		if (stateSet)
		{
			std::cout << "" << stateSet->className();
		}

		std::cout << std::endl;
		moveIn();
		osg::StateSet* ret_stateSet = CopyOp::operator()(stateSet);
		moveOut();
		return ret_stateSet;
	}

	// ״̬����copy
	virtual osg::StateAttribute* operator()(const osg::StateAttribute* attr)const
	{
		writeIndent();
		std::cout << "copying StateAttribute" << attr;
		if (attr)
		{
			std::cout << "" << attr->className();
		}
		std::cout << std::endl;
		moveIn();
		osg::StateAttribute* ret_attr = CopyOp::operator()(attr);
		moveOut();
		return ret_attr;
	}

	// ������Ϣcopy
	virtual osg::Texture* operator()(const osg::Texture* text)const
	{
		writeIndent();
		std::cout << "copying Texture" << text;
		if (text)
		{
			std::cout << " " << text->className();
		}

		std::cout << std::endl;
		moveIn();
		osg::Texture* ret_text = CopyOp::operator()(text);
		moveOut();
		return ret_text;
	}

	// ��ͼcopy
	virtual osg::Image* operator()(const osg::Image* image)const
	{
		writeIndent();
		std::cout << "copying Image" << image;

		if (image)
		{
			std::cout << " " << image->className();
		}

		std::cout << std::endl;
		moveIn();
		osg::Image* ret_image = CopyOp::operator()(image);
		moveOut();
		return ret_image;
	}
protected:
	// �ո���������
	mutable int _number;
	// �ո�����
	mutable int _blank;
};

void TestCopyOp()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Node> rootnode = osgDB::readNodeFile("glider.osg");

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(rootnode.get());

	// ǳ����һ������
	osg::ref_ptr<osg::Node> shallowCopy = dynamic_cast<osg::Node*>(rootnode->clone(osg::CopyOp::SHALLOW_COPY));
	std::cout << std::endl << "���ǳ����һ������" << std::endl << std::endl;

	// ���һ������
	osg::ref_ptr<osg::Node> deepCopy = dynamic_cast<osg::Node*>(rootnode->clone(osg::CopyOp::DEEP_COPY_ALL));
	std::cout << std::endl << "������һ������" << std::endl;;

	// �Զ��������Ϣǳ��������
	osg::ref_ptr<osg::Node> myShallowCopy = dynamic_cast<osg::Node*>(rootnode->clone(MyCopyOp(osg::CopyOp::SHALLOW_COPY)));
	std::cout << std::endl << "���һ���Զ��������Ϣǳ��������" << std::endl << std::endl;

	// �Զ��������Ϣ�������
	osg::ref_ptr<osg::Node> myDeepCopy = dynamic_cast<osg::Node*>(rootnode->clone(MyCopyOp(osg::CopyOp::SHALLOW_COPY)));
	std::cout << std::endl << "���һ���Զ��������Ϣ�������" << std::endl << std::endl;


	viewer->setUpViewInWindow(400, 400, 800, 800);
	viewer->setSceneData(rootnode.get());

	viewer->realize();
	viewer->run();

	return;
}