#include "stadfx.h"

class StripStateVisitor :public osg::NodeVisitor
{
public:
	StripStateVisitor(bool useStateSets, bool useDisplayLists, bool useVBO):
		osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN), _useStateSets(useStateSets), _useDisplayLists(useDisplayLists),
		_useVBO(useVBO)
	{

	}


public:
	bool _useStateSets;
	bool _useDisplayLists;
	bool _useVBO;

	void apply(osg::Node& node)
	{
		if (!_useStateSets && node.getStateSet())
			node.setStateSet(0);
		traverse(node);
	}

	void apply(osg::Drawable& drawable)
	{
		if (!_useStateSets && drawable.getStateSet())
		{
			drawable.setStateSet(0);
		}

		drawable.setUseDisplayList(_useDisplayLists);
		drawable.setUseVertexBufferObjects(_useVBO);
	}
};

class OptimizeImageVisitor : public osg::NodeVisitor
{
public:
	OptimizeImageVisitor(osgDB::ImageProcessor* imageProcessor, bool compressImages, bool generateMipmaps) :
		osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
		_imageProcessor(imageProcessor),
		_compressImages(compressImages),
		_generateMipmaps(generateMipmaps)
	{

	}

	osg::ref_ptr<osgDB::ImageProcessor> _imageProcessor;
	bool _compressImages;
	bool _generateMipmaps;

	void apply(osg::Node& node)
	{
		processStateSet(node.getStateSet());
	}


	void processStateSet(osg::StateSet* stateset)
	{
		if (!stateset)
			return;

		for (unsigned int ti = 0; ti < stateset->getNumTextureAttributeLists(); ++ti)
		{
			osg::StateAttribute* sa = stateset->getTextureAttribute(ti, osg::StateAttribute::TEXTURE);
			osg::Texture* texture = dynamic_cast<osg::Texture*>(sa);

			if (texture)
			{
				for (unsigned int i = 0; i < texture->getNumImages(); ++i)
				{
					processImage(texture->getImage(i));
				}
			}
		}
	}
	void processImage(osg::Image* image)
	{
		if (!image)
			return;
		if (!_imageProcessor.valid())
		{
			OSG_NOTICE << "Will be using ImageProcessor to process image " << image->getFileName() << std::endl;
		}

		else
		{
			OSG_NOTICE << "No ImageProcessor to process image " << image->getFileName() << std::endl;
		}
		OSG_NOTICE << " compressImage " << _compressImages << std::endl;
		OSG_NOTICE << " generateMipmaps " << _generateMipmaps << std::endl;
	}
};