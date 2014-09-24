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

using namespace osgCal;
using namespace osg;
using namespace osgDB;

// forward declare functions to use later.
bool Model_readLocalData(Object& obj, Input& fr);
bool Model_writeLocalData(const Object& obj, Output& fw);

// register the read and write functions with the osgDB::Registry.
RegisterDotOsgWrapperProxy CalModelNodeProxy
(
 new osgCal::Model,
 "osgCal::Model",
 "Object Node   osgCal::Model",
 &Model_readLocalData,
 &Model_writeLocalData
 );

// register the backward-compatible read and write functions with the osgDB::Registry.
/*
RegisterDotOsgWrapperProxy ModelProxyBCAL
(
 new osgCal::Model,
 "osgCal::Model",
 "Object  osgCal::Model",
 &Model_readLocalData,

 &Model_writeLocalData
 );*/

bool Model_readLocalData(osg::Object &obj, osgDB::Input &fr)
{

	std::cout <<  " loaded1" << std::endl;
	Model &sn = static_cast<Model&>(obj);
	if (fr.matchSequence("CFGfileName %s")) {
		std::string file = fr[1].getStr();
		CoreModel * core = osgCal::OsgCalManager::get()->getCoreModel(file);
		std::cout << " loaded11" << file<<std::endl;
		if (core==0   )
		{
			core = new CoreModel(); core->load(file);core->setName(file);
			std::cout << file << " loaded2" << std::endl;
			OsgCalManager::get()->addCore(file, core);
			std::cout << file << " loaded21" << std::endl;
			
		}
		//osgCal::DefaultMeshAdder ma;
		try{
			sn.load(core, new osgCal::DefaultMeshAdder());
			sn.blendCycle(0, 1, 0);//play the defaul animation else it 's cull
			sn.update(1 / 25);
			
		}
		catch (std::exception e){
			cerr << e.what() << endl;
			return false;
		}
		std::cout << file << " loaded3" << std::endl;
		return true;
	}else
	return false;
}

bool Model_writeLocalData(const Object& obj, Output& fw)
{
    const Model &sn = static_cast<const Model&>(obj);

	std::cout << " saving" << sn.getCoreModel()->getName() << std::endl;
	fw.indent() << "CFGfileName \"" << sn.getCoreModel()->getName() << "\"" << std::endl;


    return true;
}
