#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/OccluderNode>
#include <osg/StateSet>
#include <osg/ConvexPlanarOccluder>
#include <osg/BoundingBox>
#include <osg/BoundingSphere>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <iostream>

// �����ڵ��ڵ�
osg::ref_ptr<osg::Node> createOccluder(const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3, const osg::Vec3& v4)
{
	// �����ڵ��ڵ����
	osg::ref_ptr<osg::OccluderNode> occluderNode = new osg::OccluderNode();

	// �����ڵ�ƽ��
	osg::ref_ptr<osg::ConvexPlanarOccluder> cpo = new osg::ConvexPlanarOccluder();

	// �����ڵ���ƽ��
	occluderNode->setOccluder(cpo.get());
	occluderNode->setName("occluder");

	// ��ʼ��һ���ڵ�ƽ��
	osg::ConvexPlanarPolygon& occluder = cpo->getOccluder();
	occluder.add(v1);
	occluder.add(v2);
	occluder.add(v3);
	occluder.add(v4);

	// Ϊ�ڵ��滭һ���ı���
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array(occluder.getVertexList().begin(), occluder.getVertexList().end());
	geom->setVertexArray(coords);

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
	(*colors)[0].set(1.0f, 1.0f, 1.0f, 0.5f);
	geom->setColorArray(colors.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom.get());

	osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet();
	// �رչ���
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	// ʹ�û�ϣ��Ա�֤Alpha������ȷ
	stateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
	// ����͸����ȾԪ
	stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	geom->setStateSet(stateSet.get());

	// �����ı�����Ϊ�ڵ��ڵ㣬�ڵ��ڵ㱾�����߱��ڵ�����
	occluderNode->addChild(geode.get());

	return occluderNode.get();
}

osg::ref_ptr<osg::Group> createOccludesAroundModel(osg::ref_ptr<osg::Node> model)
{
	// ����������ڵ�
	osg::ref_ptr<osg::Group> scene = new osg::Group();
	scene->setName("OccluderScene");

	// �����ӽڵ�
	scene->addChild(model.get());
	model->setName("cow.osg");

	// ����ģ�͵İ�Χ��
	const osg::BoundingSphere bs = model->getBound();

	// ���ݰ�Χ�д���ǰ�������ĸ��ڵ���
	osg::BoundingBox bb;
	bb.expandBy(bs);

	// ǰ�ڵ���
	scene->addChild(createOccluder(bb.corner(0), bb.corner(1), bb.corner(5), bb.corner(4)));
	// ���ڵ���
	scene->addChild(createOccluder(bb.corner(1), bb.corner(3), bb.corner(7), bb.corner(5)));
	// ���ڵ���
	scene->addChild(createOccluder(bb.corner(2), bb.corner(0), bb.corner(4), bb.corner(6)));
	/// ���ڵ���
	scene->addChild(createOccluder(bb.corner(3), bb.corner(2), bb.corner(6), bb.corner(7)));

	return scene.get();
}

void TestOccluder()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	// �����ڵ�����
	root->addChild(createOccludesAroundModel(node.get()));

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->realize();

	viewer->run();
}