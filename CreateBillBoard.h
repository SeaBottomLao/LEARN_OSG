#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/BillBoard>
#include <osg/Texture2D>
#include <osg/image>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Node> createBillBoard(osg::ref_ptr<osg::Image> image)
{
	// 创建四边形
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

	// 设置顶点
	osg::ref_ptr<osg::Vec3Array> vecarray = new osg::Vec3Array;
	vecarray->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
	vecarray->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
	vecarray->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
	vecarray->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));

	geometry->setVertexArray(vecarray);

	// 设置法线
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(1.0f, 0.0f, 0.0f) ^ osg::Vec3(0.0f, 0.0f, 1.0f));

	geometry->setNormalArray(normal.get());
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	// 设置纹理坐标
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));

	geometry->setTexCoordArray(0, vt.get());

	// 绘制四边形
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	if (image.get())
	{
		// 状态属性对象
		osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
		
		// 创建一个Texture2D对象
		osg::ref_ptr<osg::Texture2D>  texture = new osg::Texture2D;
		texture->setImage(image); // 关联image
		
		// 关联texture纹理对象，第三个参数默认为on
		stateSet->setTextureAttributeAndModes(0, texture,osg::StateAttribute::ON);
		// 启用混用
		stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		// 关闭光照
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);

		geometry->setStateSet(stateSet.get());
	}

	// 创建告示板对象
	osg::ref_ptr<osg::Billboard> billboard1 = new osg::Billboard();

	// 设置旋转模式为绕视点
	billboard1->setMode(osg::Billboard::POINT_ROT_EYE);
	// 添加Drawable，并设置其位置，默认位置为osg::Vec3(0.0f,0.0f,0.0f)
	billboard1->addDrawable(geometry.get(), osg::Vec3(5.0f, 0.0f, 0.0f));
	osg::ref_ptr<osg::Billboard> billboard2 = new osg::Billboard();
	// 设置旋转模式为绕轴旋转，因此还需要设置旋转轴
	billboard2->setMode(osg::Billboard::AXIAL_ROT);
	// 设置旋转轴
	billboard2->setAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
	billboard2->addDrawable(geometry.get(), osg::Vec3(10.0f, 0.0f, 0.0f));

	osg::ref_ptr<osg::Group> billboard = new osg::Group();
	billboard->addChild(billboard1.get());
	billboard->addChild(billboard2.get());

	return billboard.get();
}