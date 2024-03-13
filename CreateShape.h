#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Geode> createShape()
{
	// ����һ��Ҷ�ڵ�
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// ���ð뾶�͸߶�
	float radius = 0.8f;
	float height = 1.0f;

	// ������ϸ�ȶ��󣬾�ϸ��Խ�ߣ�ϸ�־�Խ��
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	// ���þ�ϸ��Ϊ0.5f
	hints->setDetailRatio(0.5f);

	// ���һ�����壬��һ��������Ԥ����������󣬵ڶ����Ǿ�ϸ��
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints));

	// ���һ��������
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2 * radius), hints));
	// ���һ��Բ׶
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints));

	// ���һ��̫�ղ�
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height)));

	return geode.get();
}

int TestCreateShape()
{
	// ������Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ��ӵ�����
	root->addChild(createShape());
	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	return viewer->run();
}