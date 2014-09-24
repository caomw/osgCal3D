/* -*-c++-*- $Id: IO_Model.cpp 110 2012-01-13 16:59:13Z SkewMatrix@gmail.com $ */
/**
 * osgAudio - OpenSceneGraph Audio Library
 * (C) Copyright 2009-2012 byKenneth Mark Bryden
 * (programming by Chris 'Xenon' Hanson, AlphaPixel, LLC xenon at alphapixel.com)
 * based on a fork of:
 * Osg AL - OpenSceneGraph Audio Library
 * Copyright (C) 2004 VRlab, Umeå University
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * Please see COPYING file for special static-link exemption to LGPL.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */

#include <osgCal/Model>

#include <osgCal/OsgCalManager>


#include <osgDB/Registry>
#include <osgDB/Input>
#include <osgDB/Output>
#include <osgDB/FileUtils>



#include <osg/Camera>
#include <osgDB/ObjectWrapper>
#include <osgDB/InputStream>
#include <osgDB/OutputStream>
using namespace osgCal;
using namespace osg;
using namespace osgDB;


static bool checkCoreFileName(const osgCal::Model& node)
{
	return true;// node.getClearMask() != (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static bool readCoreFileName(osgDB::InputStream& is, osgCal::Model& ss)
{//assuming osg::Group serialization read is alreadydone
	ss.removeChildren(0, ss.getNumChildren());

	std::string filename;  is >> filename;
	std::cout << "read SAmple" << filename << std::endl;

	CoreModel * core = osgCal::OsgCalManager::get()->getCoreModel(filename);
	if (core == 0)
	{
		core = new CoreModel(); core->load(filename); core->setName(filename);
		std::cout << filename << " loaded2" << std::endl;
		OsgCalManager::get()->addCore(filename, core);
		std::cout << filename << " loaded21" << std::endl;

	}
	try{
		ss.load(core, new osgCal::DefaultMeshAdder());
		ss.blendCycle(0, 1, 0);//play the defaul animation else it 's cull
		ss.update(1 / 25);
		return true;

	}
	catch (std::exception e){
		cerr << e.what() << endl;
		return false;
	}
	return false;
}
static bool writeCoreFileName(osgDB::OutputStream& os, const osgCal::Model& ss)
{
	std::string filename("NamethatCantExists");
	if (ss.getCoreModel() != NULL)
		filename = ss.getCoreModel()->getName();
	os << filename << std::endl;

	return true;

}



REGISTER_OBJECT_WRAPPER(osgCalModel,
	new osgCal::Model,
	osgCal::Model,
	"osg::Object osg::Node osg::Group osgCal::Model")
{
	/*BEGIN_ENUM_SERIALIZER2(Function, osgAudio::SoundUpdateCB::ComparisonFunction, ALWAYS);
	ADD_ENUM_VALUE(NEVER);
	ADD_ENUM_VALUE(LESS);
	ADD_ENUM_VALUE(EQUAL);
	ADD_ENUM_VALUE(LEQUAL);
	ADD_ENUM_VALUE(GREATER);
	ADD_ENUM_VALUE(NOTEQUAL);
	ADD_ENUM_VALUE(GEQUAL);
	ADD_ENUM_VALUE(ALWAYS);
	END_ENUM_SERIALIZER();  // _comparisonFunc
	ADD_OBJECT_SERIALIZER(SoundState, osgAudio::SoundState, NULL);  // _eventCallback
	ADD_OBJECT_SERIALIZER(OccludeCallback, osgAudio::OccludeCallback, NULL);*/
	//ADD_FLOAT_SERIALIZER(ReferenceValue, 1.0f);  // _referenceValue

		ADD_USER_SERIALIZER(CoreFileName);
	//ADD_BOOL_SERIALIZER(UpdateEnable, true);
}