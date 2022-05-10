#include "helpers.h"

#include <vtksys/SystemTools.hxx>
#include <vtkPolyDataReader.h>

// meshes
#include <vtkSphereSource.h>
#include <vtkOBJReader.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSTLReader.h>

// points
#include <vtkParticleReader.h>
#include <vtkSimplePointsReader.h>

bool _3DRPHelpers::pclLoadSTL(const std::string fileNamePath, pcl::PolygonMesh& polyMesh) {
	pcl::io::loadPolygonFileSTL(fileNamePath, polyMesh);

	return polyMesh.polygons.size() != 0;
}
bool _3DRPHelpers::pclSaveSTL(const std::string fileNamePath, pcl::PolygonMesh& polyMesh, bool isBinaryFormat) {
	if (polyMesh.polygons.size() == 0) return false;
	return pcl::io::savePolygonFileSTL(fileNamePath, polyMesh, isBinaryFormat);
}

bool _3DRPHelpers::vtkLoadSTL(const std::string fileNamePath, vtkSmartPointer<vtkPolyData> polyData) {

	vtkNew<vtkSTLReader> reader;
	reader->SetFileName(fileNamePath.c_str());
	reader->Update();
	polyData = reader->GetOutput();

	return polyData->GetNumberOfPoints() == 0 || polyData->GetNumberOfVerts() == 0;
}
bool _3DRPHelpers::vtkSaveSTL(const std::string fileNamePath, const vtkSmartPointer<vtkPolyData> polyData, bool isBinaryFormat) {

	if (polyData->GetNumberOfPoints() == 0 || polyData->GetNumberOfVerts() == 0) return false;

	// FROM: https://kitware.github.io/vtk-examples/site/Cxx/IO/WriteSTL/
	vtkNew<vtkSTLWriter> stlWriter;
	stlWriter->SetFileName(fileNamePath.c_str());
	stlWriter->SetFileType(isBinaryFormat);
	stlWriter->SetInputData(polyData);
	stlWriter->Write();

	return true;
}

// currently broken  please use the other override
bool _3DRPHelpers::ReadPolyData(const char* fileName, vtkSmartPointer<vtkPolyData> polyData)
{
    std::string extension =
        vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));

    // Drop the case of the extension
    std::transform(extension.begin(), extension.end(), extension.begin(),
        ::tolower);

    if (extension == ".ply")
    {
        vtkNew<vtkPLYReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData.TakeReference(reader->GetOutput());
    }
    else if (extension == ".obj")
    {
        vtkNew<vtkOBJReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData.TakeReference(reader->GetOutput());
    }
    else if (extension == ".stl")
    {
        vtkNew<vtkSTLReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData.TakeReference(reader->GetOutput());
    }
    else if (extension == ".vtk")
    {
        vtkNew<vtkPolyDataReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData.TakeReference(reader->GetOutput());
    }
    //else if (extension == ".pcd")
    //{
    //        MyCloud myCloud;
    //        string filePath = fromQString(fileInfo.filePath());
    //        int status = -1;
    //        status = pcl::io::loadPCDFile(filePath, *(myCloud.cloud));
    //    
    //        bool hasCloud = (status == 0);
    //        // There is no polygon mesh loader for pcd file in PCL
    //        bool hasMesh = false;
    //        myCloud.init(fileInfo, hasCloud, hasMesh);
    //    
    //        return myCloud;
    //}
    else // try to decode file as a point cloud
    {
        // FROM: https://kitware.github.io/vtk-examples/site/Cxx/IO/ParticleReader/
        // Particles.raw supplied by VTK is big endian encoded
        // std::string filePath = "C:\\VTK\\vtkdata-5.8.0\\Data\\Particles.raw";
        vtkNew<vtkParticleReader> raw_points;

        raw_points->SetFileName(fileName);
        // if nothing gets displayed or totally wrong, swap the endianness
        raw_points->SetDataByteOrderToBigEndian();
        raw_points->Update();
        polyData.TakeReference(raw_points->GetOutput());

        if (polyData->GetNumberOfPoints() == 0 || polyData->GetNumberOfVerts() == 0)
        {
            // FROM: https://kitware.github.io/vtk-examples/site/Cxx/IO/SimplePointsReader/
            vtkNew<vtkSimplePointsReader> simple_points;
            simple_points->SetFileName(fileName);
            simple_points->Update();
            polyData = simple_points->GetOutput();
        }


    }

    if (polyData->GetNumberOfPoints() == 0 || polyData->GetNumberOfVerts() == 0) // vertices is the most atomic geametric-data when ther is no verts, there is no geometry
        return false;

    return true;
}


vtkSmartPointer<vtkPolyData> _3DRPHelpers::ReadPolyData(const char* fileName)
{
    vtkSmartPointer<vtkPolyData> polyData;

    std::string extension =
        vtksys::SystemTools::GetFilenameLastExtension(std::string(fileName));

    // Drop the case of the extension
    std::transform(extension.begin(), extension.end(), extension.begin(),
        ::tolower);

    if (extension == ".ply")
    {
        vtkNew<vtkPLYReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData = reader->GetOutput();
    }
    else if (extension == ".obj")
    {
        vtkNew<vtkOBJReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData = reader->GetOutput();
    }
    else if (extension == ".stl")
    {
        vtkNew<vtkSTLReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData = reader->GetOutput();
    }
    else if (extension == ".vtk")
    {
        vtkNew<vtkPolyDataReader> reader;
        reader->SetFileName(fileName);
        reader->Update();
        polyData = reader->GetOutput();
    }
    else // try to decode file as a point cloud
    {
        // FROM: https://kitware.github.io/vtk-examples/site/Cxx/IO/ParticleReader/
        // Particles.raw supplied by VTK is big endian encoded
        // std::string filePath = "C:\\VTK\\vtkdata-5.8.0\\Data\\Particles.raw";
        vtkNew<vtkParticleReader> raw_points;

        raw_points->SetFileName(fileName);
        // if nothing gets displayed or totally wrong, swap the endianness
        raw_points->SetDataByteOrderToBigEndian();
        raw_points->Update();
        polyData = raw_points->GetOutput();

        if (polyData->GetNumberOfPoints() == 0 || polyData->GetNumberOfVerts() == 0)
        {
            // FROM: https://kitware.github.io/vtk-examples/site/Cxx/IO/SimplePointsReader/
            vtkNew<vtkSimplePointsReader> simple_points;
            simple_points->SetFileName(fileName);
            simple_points->Update();
            polyData = simple_points->GetOutput();
        }


    }

    return polyData;
}

pcl::PolygonMesh _3DRPHelpers::vtkModelToPCLModel(vtkSmartPointer<vtkPolyData> vtkModel) {
	pcl::PolygonMesh polyMesh;

	vtkSaveSTL("temp.stl", vtkModel, true);
	pclLoadSTL("temp.stl", polyMesh);
	std::string s = "temp.stl";
	remove(s.c_str());

	return polyMesh;
}

vtkSmartPointer<vtkPolyData> _3DRPHelpers::pclModelToVTKModel(pcl::PolygonMesh pclModel) {
	vtkSmartPointer<vtkPolyData> polyData;

	pclSaveSTL("temp.stl", pclModel, true);
	vtkLoadSTL("temp.stl", polyData);
	std::string s = "temp.stl";
	remove(s.c_str());

	return polyData;
}