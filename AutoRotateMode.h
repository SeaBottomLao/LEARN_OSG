#include <osg/Node>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Group>
#include <osg/AutoTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>


#include <osgText/Text>

#include <osgUtil/Optimizer>

#include <iostream>

// �����Զ��任�ڵ�
osg::ref_ptr<osg::Node> createAutoTransform(osg::Vec3& position, float size, std::string& label,
	osg::AutoTransform::AutoRotateMode autoMode,osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// ����
	std::string font("fonts/cour.ttf");

	// ����Text����
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	geode->addDrawable(text.get());

	// ��������
	text->setFont(font);
	// ��������ķֱ��ʣ�Ĭ��Ϊ32*32
	text->setFontResolution(128.0f, 128.0f);
	// ��������Ĵ�С
	text->setCharacterSize(size);
	// ���ö���ķ�ʽ
	text->setAlignment(osgText::Text::CENTER_CENTER);
	// ���÷���
	text->setAxisAlignment(axisAlignment);
	// ��������
	text->setText(label);

	// �رչ���
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	// �����Զ��任�ڵ�
	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform();
	// ����ӽڵ�
	at->addChild(geode.get());
	// �����Զ��任��ʽ
	at->setAutoRotateMode(autoMode);
	// ������Ļ��С�����Žڵ㣬Ĭ��Ϊfalse������Ϊtrueʱ���ڵ��޷�����
	at->setAutoScaleToScreen(false);
	// �������ŵ�������С����
	at->setMinimumScale(0.0f);
	at->setMaximumScale(5.0f);
	// ����λ��
	at->setPosition(position);

	return at.get();
}