/*=========================================================================

  Programme :   OTB (ORFEO ToolBox)
  Auteurs   :   CS - T.Feuvrier
  Language  :   C++
  Date      :   17 janvier 2005
  Version   :   
  Role      :   Classe IO image pour le format GDAL
  $Id$

=========================================================================*/
#ifndef __otbGDALImageIO_h
#define __otbGDALImageIO_h

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

/* C++ Libraries */
#include <string>
#include "stdlib.h"

/* ITK Libraries */
#include "itkImageIOBase.h"

#include "otbMetaDataKey.h"


/* GDAL Libraries */
#include "gdal.h"
#include "gdal_priv.h"
#include "cpl_string.h"
#include "cpl_conv.h"
#include "ogr_spatialref.h"
#include "ogr_srs_api.h"


namespace otb
{

/** \class GDALImageIO
 *
 * \brief ImageIO object for reading (not writing) GDAL images
 *
 * The streaming read is implemented.
 *
 * \ingroup IOFilters
 *
 */
class ITK_EXPORT GDALImageIO : public itk::ImageIOBase,
			       public MetaDataKey
{
public:

  typedef unsigned char InputPixelType;
  
  /** Standard class typedefs. */
  typedef GDALImageIO            Self;
  typedef itk::ImageIOBase  Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(GDALImageIO, itk::ImageIOBase);

  /** Set/Get the level of compression for the output images.
   *  0-9; 0 = none, 9 = maximum. */
  itkSetMacro(CompressionLevel, int);
  itkGetMacro(CompressionLevel, int);

  /*-------- This part of the interface deals with reading data. ------ */

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanReadFile(const char*);
  
  /** Determine the file type. Returns true if the ImageIO can stream read the specified file */
  virtual bool CanStreamRead(){  return true; };

  /** Set the spacing and dimention information for the set filename. */
  virtual void ReadImageInformation();
 
  /** Reads the data from disk into the memory buffer provided. */
  virtual void Read(void* buffer);
    
  /** Reads 3D data from multiple files assuming one slice per file. */
  virtual void ReadVolume(void* buffer);

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanWriteFile(const char*);

  /** Determine the file type. Returns true if the ImageIO can stream write the specified file */
  virtual bool CanStreamWrite() { return false; };

  /** Writes the spacing and dimentions of the image.
   * Assumes SetFileName has been called with a valid file name. */
  virtual void WriteImageInformation();

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegion has been set properly. */
  virtual void Write(const void* buffer);

  void SampleImage(void* buffer,int XBegin, int YBegin, int SizeXRead, int SizeYRead, int XSample, int YSample);
  
protected:
  /** Construtor.*/
  GDALImageIO();
  /** Destructor.*/
  ~GDALImageIO();
  
  void PrintSelf(std::ostream& os, itk::Indent indent) const;
  /** Read all information on the image*/
  void InternalReadImageInformation();
  /** Write all information on the image*/
  void InternalWriteImageInformation();
  /** Dimension along Ox of the image*/
  int m_width;
  /** Dimension along Oy of the image*/
  int m_height;
  /** Number of bands of the image*/
  int m_NbBands;
  /** Buffer*/
  //float **pafimas;
  
  /** Determines the level of compression for written files. 
   *  Range 0-9; 0 = none, 9 = maximum , default = 4 */
  int m_CompressionLevel;
  const char* m_currentfile;

private:
  GDALImageIO(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** M�thode analyse le nom du fichier a ouvrir. S'il s'agit d'un r�pertoire, 
    * on regarde s'il contient un produit CEOS (fichier "DAT...")
    * Dans ce cas, GdalFileName contient le nom du fichier a ouvrir. Sinon GdalFileName contient filename
    */
  bool GetGdalImageFileName( const char * filename, std::string & GdalFileName );

  void TypeConversion(const char* extension, std::string* extGDAL);

  /** GDAL parameters. */
  GDALDataset* m_poDataset;
  GDALRasterBand** m_poBands;
  GDALDataType m_PxType;
  /** Nombre d'octets par pixel */
  int           m_NbOctetPixel;
  
  bool GDALInfoReportCorner( const char * corner_name, double x, double y,
                           double &dfGeoX, double &dfGeoY);

};

} // end namespace otb

#endif // __otbGDALImageIO_h
