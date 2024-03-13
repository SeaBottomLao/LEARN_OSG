//#include <iostream>
//#include <osgViewer/Viewer>
//#include <osg/Geode>
//#include <osg/ShapeDrawable>
//#include <osgShadow/ShadowedScene>
//#include <osgShadow/ShadowMap>
//#include <osgDB/ReadFile>
//#include <osgDB/WriteFile>
//
//#include <osgUtil/Optimizer>
//
//#include <Windows.h>
//#include <string>
//#include <algorithm>
//#include "CoordinateConvert.h"
//#include "CreateBillboard.h"
//#include "AutoRotateMode.h"
//#include "ImposerNode.h"
//#include "Occluder.h"
//#include "EarthCoordinate.h"
//#include "CopyOp.h"
//#include "CreateQuar.h"
//#include "CreateShape.h"
//#include "CreateTesslator.h"
//#include "Simplifier.h"
//#include "TriStripVisitor.h"
#include "stadfx.h"
//int main()
//{
//	//CreateTriStripVisitor();
//	return 0;
//}


//int main()
//{
//	// 创建Viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// 创建一个节点，读取一个牛模型
//	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");
//
//	// 创建一个节点，读取一个滑翔机模型
//	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");
//
//	// 创建一个细节层次LOD节点
//	osg::ref_ptr<osg::LOD> lode = new osg::LOD();
//	// 添加子节点，在0~30范围内显示滑翔机
//	lode->addChild(node1.get(), 0.0f, 30.0f);
//	// 添加子节点，在30~100范围内显示滑翔机
//	lode->addChild(node2.get(), 30.0f, 100.0f);
//
//	// 写入lode.osg文件
//	osgDB::writeNodeFile(*lode.get(), "lode.osg");
//
//	// 添加到场景
//	root->addChild(lode.get());
//
//	// 优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setSceneData(root.get());
//	viewer->realize();
//
//	viewer->run();
//
//	return 0;
//}
//// 开关节点示例
//int main()
//{
//	// 创建viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// 创建一个节点，读取牛模型
//	osg::ref_ptr<osg::Node> node1 = new osg::Node();
//	node1 = osgDB::readNodeFile("cow.osg");
//	// 创建一个节点，读取滑翔机模型
//	osg::ref_ptr<osg::Node> node2 = new osg::Node();
//	node2 = osgDB::readNodeFile("bignathan.osg");
//	// 创建一个开关节点，只渲染滑翔机而不渲染牛
//	osg::ref_ptr<osg::Switch> swtich = new osg::Switch();
//	// 添加牛的模型，但不渲染，默认为true
//	swtich->addChild(node1.get(), false);
//
//	// 添加滑翔机模型，状态为渲染
//	swtich->addChild(node2.get(), true);
//	root->addChild(swtich.get());
//
//	// 优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setSceneData(root.get());
//	viewer->realize();
//
//	return viewer->run();
//
//}
//int main()
//{
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	std::string text("Fly To Sky");
//
//	/*
//	* 3种变换模式
//	* Rotate_To_screen 自动朝向屏幕
//	* Rotate_To_screen 自动朝向相机
//	* No_Rotation 无
//	*/
//	// 添加Rotate_To_Screen 模式变换节点
//	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f), 60.0f, text, osg::AutoTransform::ROTATE_TO_CAMERA, osgText::Text::XY_PLANE));
//
//	// 添加 ROTATE_TO_SCREEN模式变换节点
//	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f), 60.0f, text, osg::AutoTransform::NO_ROTATION, osgText::Text::XY_PLANE));
//
//	// 优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setSceneData(root.get());
//	viewer->realize();
//	return viewer->run();
//}
//std::string GetCurrentPath()
//{
//	char path[500];
//	GetCurrentDirectory(500, path);
//
//	std::string curPath(path);
//	std::replace(curPath.begin(),curPath.end(), '\\', '/');
//
//	return curPath;
//}
//// 矩阵变换节点
//int main()
//{
//	// 创建Viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	// 创建场景组节点
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// 创建一个节点，读取牛的模型
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
//	
//	// 创建矩阵变换节点mt1
//	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform();
//	// 创建一个矩阵
//	osg::Matrix m;
//	// 在x方向平移10个单位
//	m.makeTranslate(osg::Vec3(10.0f, 0.0f, 0.0f));
//	// 绕X轴体旋转45度
//	m.makeRotate(45.0f,1.0f,0.0f,0.0f);
//	// 设置矩阵
//	mt1->setMatrix(m);
//	// 添加子节点
//	mt1->addChild(node.get());
//
//	// 创建矩阵变换节点mt2
//	osg::ref_ptr<osg::MatrixTransform> mt2 = new osg::MatrixTransform();
//	// 创建一个矩阵
//	osg::Matrix t;
//	// 在X负方向上平移10个单位
//	t.makeTranslate(osg::Vec3(-10.0f, 0.0f, 0.0f));
//	// 设置矩阵
//	mt2->setMatrix(t);
//	// 添加子节点
//	mt2->addChild(node.get());
//
//	// 添加到场景
//	root->addChild(mt1.get());
//	root->addChild(mt2.get());
//
//	// 优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	// 设置场景数据
//	viewer->setSceneData(root.get());
//
//	// 初始化并创建窗口
//	viewer->realize();
//
//	// 开始渲染
//	return viewer->run();
//}
//int main()
//{
//	// 创建viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	// 创建场景组节点
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//	// 创建一个节点，读取牛的模型
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
//
//	// 创建位置变换节点pat1
//	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform();
//	// 设置位置为osg::Vec3(-10.0f,0.0f,0.0f)
//	pat1->setPosition(osg::Vec3(-10.0f, 0.0f, 0.0f));
//
//	// 设置缩放，在X、Y、Z方向都缩小一倍
//	pat1->setScale(osg::Vec3(0.5f, 0.5f, 0.5f));
//	// 添加子节点
//	pat1->addChild(node.get());
//
//	// 创建位置变换节点pat2
//	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform();
//	// 设置位置为osg:;Vec3(10.0f,0.0f,0.0f)
//	pat2->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));
//	// 添加子节点
//	pat2->addChild(node.get());
//
//	// 添加到场景
//	root->addChild(pat1.get());
//	root->addChild(pat2.get());
//
//	// 优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	// 设置场景数据
//	viewer->setSceneData(root.get());
//	// 初始化并创建窗口
//	viewer->realize();
//
//	// 开始渲染
//	return viewer->run();
//}
//int main(int argc, char* argv[])
//{
//	std::cout << "My first osg Application" << std::endl;
//	// 创建Viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
//	
//	// 创建场景组节点
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// 读取图像
//	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("tree0.rgba");
//	
//	// 缩放，达到合适的大小
//	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
//	pat->setScale(osg::Vec3(5.0f, 5.0f, 5.0f));
//	pat->addChild(createBillBoard(image.get()));
//
//	root->addChild(pat.get());
//	root->addChild(osgDB::readNodeFile("cow.osg"));
//
//	//// 创建一个节点，读取牛的模型
//	//osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(GetCurrentPath() + "/cow.osg");
//	//
//	//// 创建一个节点，读取马的模型
//	//osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile(GetCurrentPath() + "/dumptruck.osg");
//	//// 添加到场景
//	//root->addChild(node.get());
//	//root->addChild(node1.get());
//	// 优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setUpViewInWindow(400, 400, 800, 800);
//	viewer->setSceneData(root.get());
//	viewer->realize();
//	/*osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(200.0f,200.0f,200.0f), 100.0)));
//
//	osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable;
//	shape1->setShape(new osg::Box(osg::Vec3(), 100, 100, 100));
//	geode->addDrawable(shape1);
//
//	viewer->setSceneData(geode);*/
//	return viewer->run();
//}