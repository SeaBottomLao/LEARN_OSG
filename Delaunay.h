//#include "stadfx.h"
//
//
//void TestDelaunay()
//{
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//	// ����鿴�ڶ����֮���л����Բ鿴������
//	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
//
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// ������������
//	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
//
//	// ���㶥������Ĵ�С
//	unsigned int n = sizeof(coords) / sizeof(float[3]);
//
//	// ��Ӷ�������
//	for (unsigned int i = 0; i < n; i++)
//	{
//		coords->push_back(osg::Vec3(coords[i][0],coords[i][1],coords[i][2]))
//	}
//}