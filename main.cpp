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
//	// ����Viewer���󣬳��������
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// ����һ���ڵ㣬��ȡһ��ţģ��
//	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");
//
//	// ����һ���ڵ㣬��ȡһ�������ģ��
//	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");
//
//	// ����һ��ϸ�ڲ��LOD�ڵ�
//	osg::ref_ptr<osg::LOD> lode = new osg::LOD();
//	// ����ӽڵ㣬��0~30��Χ����ʾ�����
//	lode->addChild(node1.get(), 0.0f, 30.0f);
//	// ����ӽڵ㣬��30~100��Χ����ʾ�����
//	lode->addChild(node2.get(), 30.0f, 100.0f);
//
//	// д��lode.osg�ļ�
//	osgDB::writeNodeFile(*lode.get(), "lode.osg");
//
//	// ��ӵ�����
//	root->addChild(lode.get());
//
//	// �Ż���������
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
//// ���ؽڵ�ʾ��
//int main()
//{
//	// ����viewer���󣬳��������
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// ����һ���ڵ㣬��ȡţģ��
//	osg::ref_ptr<osg::Node> node1 = new osg::Node();
//	node1 = osgDB::readNodeFile("cow.osg");
//	// ����һ���ڵ㣬��ȡ�����ģ��
//	osg::ref_ptr<osg::Node> node2 = new osg::Node();
//	node2 = osgDB::readNodeFile("bignathan.osg");
//	// ����һ�����ؽڵ㣬ֻ��Ⱦ�����������Ⱦţ
//	osg::ref_ptr<osg::Switch> swtich = new osg::Switch();
//	// ���ţ��ģ�ͣ�������Ⱦ��Ĭ��Ϊtrue
//	swtich->addChild(node1.get(), false);
//
//	// ��ӻ����ģ�ͣ�״̬Ϊ��Ⱦ
//	swtich->addChild(node2.get(), true);
//	root->addChild(swtich.get());
//
//	// �Ż���������
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
//	* 3�ֱ任ģʽ
//	* Rotate_To_screen �Զ�������Ļ
//	* Rotate_To_screen �Զ��������
//	* No_Rotation ��
//	*/
//	// ���Rotate_To_Screen ģʽ�任�ڵ�
//	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f), 60.0f, text, osg::AutoTransform::ROTATE_TO_CAMERA, osgText::Text::XY_PLANE));
//
//	// ��� ROTATE_TO_SCREENģʽ�任�ڵ�
//	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f), 60.0f, text, osg::AutoTransform::NO_ROTATION, osgText::Text::XY_PLANE));
//
//	// �Ż���������
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
//// ����任�ڵ�
//int main()
//{
//	// ����Viewer���󣬳��������
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	// ����������ڵ�
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// ����һ���ڵ㣬��ȡţ��ģ��
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
//	
//	// ��������任�ڵ�mt1
//	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform();
//	// ����һ������
//	osg::Matrix m;
//	// ��x����ƽ��10����λ
//	m.makeTranslate(osg::Vec3(10.0f, 0.0f, 0.0f));
//	// ��X������ת45��
//	m.makeRotate(45.0f,1.0f,0.0f,0.0f);
//	// ���þ���
//	mt1->setMatrix(m);
//	// ����ӽڵ�
//	mt1->addChild(node.get());
//
//	// ��������任�ڵ�mt2
//	osg::ref_ptr<osg::MatrixTransform> mt2 = new osg::MatrixTransform();
//	// ����һ������
//	osg::Matrix t;
//	// ��X��������ƽ��10����λ
//	t.makeTranslate(osg::Vec3(-10.0f, 0.0f, 0.0f));
//	// ���þ���
//	mt2->setMatrix(t);
//	// ����ӽڵ�
//	mt2->addChild(node.get());
//
//	// ��ӵ�����
//	root->addChild(mt1.get());
//	root->addChild(mt2.get());
//
//	// �Ż���������
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	// ���ó�������
//	viewer->setSceneData(root.get());
//
//	// ��ʼ������������
//	viewer->realize();
//
//	// ��ʼ��Ⱦ
//	return viewer->run();
//}
//int main()
//{
//	// ����viewer���󣬳��������
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	// ����������ڵ�
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//	// ����һ���ڵ㣬��ȡţ��ģ��
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
//
//	// ����λ�ñ任�ڵ�pat1
//	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform();
//	// ����λ��Ϊosg::Vec3(-10.0f,0.0f,0.0f)
//	pat1->setPosition(osg::Vec3(-10.0f, 0.0f, 0.0f));
//
//	// �������ţ���X��Y��Z������Сһ��
//	pat1->setScale(osg::Vec3(0.5f, 0.5f, 0.5f));
//	// ����ӽڵ�
//	pat1->addChild(node.get());
//
//	// ����λ�ñ任�ڵ�pat2
//	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform();
//	// ����λ��Ϊosg:;Vec3(10.0f,0.0f,0.0f)
//	pat2->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));
//	// ����ӽڵ�
//	pat2->addChild(node.get());
//
//	// ��ӵ�����
//	root->addChild(pat1.get());
//	root->addChild(pat2.get());
//
//	// �Ż���������
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	// ���ó�������
//	viewer->setSceneData(root.get());
//	// ��ʼ������������
//	viewer->realize();
//
//	// ��ʼ��Ⱦ
//	return viewer->run();
//}
//int main(int argc, char* argv[])
//{
//	std::cout << "My first osg Application" << std::endl;
//	// ����Viewer���󣬳��������
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
//	
//	// ����������ڵ�
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	// ��ȡͼ��
//	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("tree0.rgba");
//	
//	// ���ţ��ﵽ���ʵĴ�С
//	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
//	pat->setScale(osg::Vec3(5.0f, 5.0f, 5.0f));
//	pat->addChild(createBillBoard(image.get()));
//
//	root->addChild(pat.get());
//	root->addChild(osgDB::readNodeFile("cow.osg"));
//
//	//// ����һ���ڵ㣬��ȡţ��ģ��
//	//osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(GetCurrentPath() + "/cow.osg");
//	//
//	//// ����һ���ڵ㣬��ȡ���ģ��
//	//osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile(GetCurrentPath() + "/dumptruck.osg");
//	//// ��ӵ�����
//	//root->addChild(node.get());
//	//root->addChild(node1.get());
//	// �Ż���������
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