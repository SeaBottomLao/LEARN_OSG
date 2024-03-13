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

// 创建自动变换节点
osg::ref_ptr<osg::Node> createAutoTransform(osg::Vec3& position, float size, std::string& label,
	osg::AutoTransform::AutoRotateMode autoMode,osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// 字体
	std::string font("fonts/cour.ttf");

	// 创建Text对象
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	geode->addDrawable(text.get());

	// 设置字体
	text->setFont(font);
	// 设置字体的分辨率，默认为32*32
	text->setFontResolution(128.0f, 128.0f);
	// 设置字体的大小
	text->setCharacterSize(size);
	// 设置对齐的方式
	text->setAlignment(osgText::Text::CENTER_CENTER);
	// 设置方向
	text->setAxisAlignment(axisAlignment);
	// 设置文字
	text->setText(label);

	// 关闭光照
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	// 创建自动变换节点
	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform();
	// 添加子节点
	at->addChild(geode.get());
	// 设置自动变换方式
	at->setAutoRotateMode(autoMode);
	// 根据屏幕大小来缩放节点，默认为false，设置为true时，节点无法缩放
	at->setAutoScaleToScreen(false);
	// 设置缩放的最大和最小比例
	at->setMinimumScale(0.0f);
	at->setMaximumScale(5.0f);
	// 设置位置
	at->setPosition(position);

	return at.get();
}