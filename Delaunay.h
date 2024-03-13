//#include "stadfx.h"
//
//
//void TestDelaunay()
//{
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//	// 方便查看在多边形之间切换，以查看三角网
//	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
//
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// 创建顶点数组
//	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
//
//	// 计算顶点数组的大小
//	unsigned int n = sizeof(coords) / sizeof(float[3]);
//
//	// 添加顶点数据
//	for (unsigned int i = 0; i < n; i++)
//	{
//		coords->push_back(osg::Vec3(coords[i][0],coords[i][1],coords[i][2]))
//	}
//}