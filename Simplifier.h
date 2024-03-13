#include "stadfx.h"

int CreateSimplifier()
{
	// ����Viewer���󡢳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	// �л�����ģʽ������Ƚ�ģ��
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// �����������ʣ���������Խ�󣬼�Խ��
	// ��������ԽС����Խ��
	float fSampleRatio = 0.3f;
	// ���õ��������
	float fMaxError = 4.0f;

	// �����򻯶���
	osgUtil::Simplifier simplifier(fSampleRatio, fMaxError);

	// ��ȡţ��ģ��
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");
	// ���ţ��ģ�͵�node2
	osg::ref_ptr<osg::Node> node2 = (osg::Node*)(node1->clone(osg::CopyOp::DEEP_COPY_ALL));

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	// ����λ��
	pat->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));
	// ����ӽڵ�
	pat->addChild(node2.get());

	// �򻯴���
	pat->accept(simplifier);

	// ��ӵ�����
	root->addChild(node1.get());
	root->addChild(pat.get());

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	return viewer->run();
}