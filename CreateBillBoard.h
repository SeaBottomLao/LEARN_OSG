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
	// �����ı���
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

	// ���ö���
	osg::ref_ptr<osg::Vec3Array> vecarray = new osg::Vec3Array;
	vecarray->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
	vecarray->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
	vecarray->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
	vecarray->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));

	geometry->setVertexArray(vecarray);

	// ���÷���
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(1.0f, 0.0f, 0.0f) ^ osg::Vec3(0.0f, 0.0f, 1.0f));

	geometry->setNormalArray(normal.get());
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	// ������������
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));

	geometry->setTexCoordArray(0, vt.get());

	// �����ı���
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	if (image.get())
	{
		// ״̬���Զ���
		osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
		
		// ����һ��Texture2D����
		osg::ref_ptr<osg::Texture2D>  texture = new osg::Texture2D;
		texture->setImage(image); // ����image
		
		// ����texture������󣬵���������Ĭ��Ϊon
		stateSet->setTextureAttributeAndModes(0, texture,osg::StateAttribute::ON);
		// ���û���
		stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		// �رչ���
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);

		geometry->setStateSet(stateSet.get());
	}

	// ������ʾ�����
	osg::ref_ptr<osg::Billboard> billboard1 = new osg::Billboard();

	// ������תģʽΪ���ӵ�
	billboard1->setMode(osg::Billboard::POINT_ROT_EYE);
	// ���Drawable����������λ�ã�Ĭ��λ��Ϊosg::Vec3(0.0f,0.0f,0.0f)
	billboard1->addDrawable(geometry.get(), osg::Vec3(5.0f, 0.0f, 0.0f));
	osg::ref_ptr<osg::Billboard> billboard2 = new osg::Billboard();
	// ������תģʽΪ������ת����˻���Ҫ������ת��
	billboard2->setMode(osg::Billboard::AXIAL_ROT);
	// ������ת��
	billboard2->setAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
	billboard2->addDrawable(geometry.get(), osg::Vec3(10.0f, 0.0f, 0.0f));

	osg::ref_ptr<osg::Group> billboard = new osg::Group();
	billboard->addChild(billboard1.get());
	billboard->addChild(billboard2.get());

	return billboard.get();
}