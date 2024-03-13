#include "stadfx.h"

// ʹ�÷ָ������ư������
osg::ref_ptr<osg::Geode> tesslatorGeometry()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	geode->addDrawable(geom.get());

	// ������һЩ��������
	// ǽ
	const float wall[5][3] =
	{
		{2200.0f,0.0f,1130.0f},
		{2600.0f,0.0f,1130.0f},
		{2600.0f,0.0f,1340.0f},
		{2400.0f,0.0f,1440.0f},
		{2200.0f,0.0f,1340.0f}
	};

	// ���ö�������
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
	geom->setVertexArray(coords);

	// ���÷���
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(normal.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	// ���ǽ
	for (int i = 0; i < 5; i++)
	{
		coords->push_back(osg::Vec3(wall[i][0], wall[i][1], wall[i][2]));
	}

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON, 0, 5));

	// �����ָ񻯶���
	osg::ref_ptr<osgUtil::Tessellator> tscx = new osgUtil::Tessellator();
	// ���÷ָ�����Ϊ������
	tscx->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
	// ���ò�������ʾ������
	tscx->setBoundaryOnly(false);
	// ���û��ƹ���
	tscx->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);

	// ʹ�÷ָ�
	tscx->retessellatePolygons(*geom.get());


	return geode.get();
}

int TestCreateTesslator()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ��ӻ��ƵĶ����
	osg::ref_ptr<osg::Geode> geode = tesslatorGeometry();
	root->addChild(geode.get());

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	return viewer->run();
}