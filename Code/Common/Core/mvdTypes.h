/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __mvdTypes_h
#define __mvdTypes_h

//
// Configuration include.
//// Included at first position before any other ones.
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "ConfigureMonteverdi2.h"
#endif //tag=QT4-boost-compatibility


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtGui>

//
// System includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include <exception>
#endif //tag=QT4-boost-compatibility

//
// ITK includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include <itkArray.h>
#include <itkImageRegion.h>
#endif //tag=QT4-boost-compatibility

//
// OTB includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include <otbImage.h>
#include <otbImageFileReader.h>
#include <otbImageFileWriter.h>
#include <otbVectorImage.h>
#endif //tag=QT4-boost-compatibility


////
//// O T B
////

// TODO: Contribute to OTB!
namespace otb
{
/**
 */
template< typename T2, typename T1 >
inline
itk::SmartPointer< T2 >
DynamicCast( const itk::SmartPointer< T1 >& p1 )
{
  return
    typename itk::SmartPointer< T2 >(
      dynamic_cast< typename itk::SmartPointer< T2 >::ObjectType* >(
	p1.GetPointer()
      )
    );
}

/**
 */
template< typename T2, typename T1 >
inline
itk::SmartPointer< const T2 >
ConstCast( const itk::SmartPointer< T1 >& p1 )
{
  return
    typename itk::SmartPointer< const T2 >(
      const_cast< typename itk::SmartPointer< const T2 >::ObjectType* >(
	p1.GetPointer()
      )
    );
}

/**
 */
template< typename T2, typename T1 >
inline
itk::SmartPointer< T2 >
ConstCast( const itk::SmartPointer< const T1 >& p1 )
{
  return
    typename itk::SmartPointer< T2 >(
      const_cast< typename itk::SmartPointer< T2 >::ObjectType* >(
	p1.GetPointer()
      )
    );
}

} // end of namespace otb.


////
//// M V D 2
////

//
// Monteverdi includes (sorted by alphabetic order)

//
// External classes pre-declaration.
namespace
{
}

//
// Type definitions.
namespace mvd
{

/*******************************************************************************/
/* Enumerations                                                                */

/**
 */
enum Bound
{
  BOUND_LOWER = 0,
  BOUND_UPPER,
  BOUND_COUNT
};

/**
 */
enum Effect
{
  EFFECT_NONE = 0,
  //
  EFFECT_CHESSBOARD,
  EFFECT_GRADIENT,
  EFFECT_LOCAL_CONTRAST,
  EFFECT_LOCAL_TRANSLUCENCY,
  EFFECT_NORMAL,
  EFFECT_SPECTRAL_ANGLE,
  EFFECT_SWIPE_H,
  EFFECT_SWIPE_V,
  //
  EFFECT_COUNT
};

/**
 * Constant naming bound values.
 */
extern
const char*
BOUND_NAMES[ BOUND_COUNT ];

/**
 * Constant naming effect values.
 */
Monteverdi2_EXPORT
extern
char const * const
EFFECT_NAME[ EFFECT_COUNT ];

/*******************************************************************************/
/* Type definitions of scalar values.                                          */

/**
 */
typedef unsigned int CountType;

/**
 */
typedef Monteverdi2_FLOATING_TYPE RealType;

/**
 */
typedef RealType ComponentType;

/**
 */
typedef itk::VariableLengthVector< RealType > VectorPixelType;

/*******************************************************************************/
/* Type definitions of STL realization.                                        */

/**
 */
typedef std::vector< std::string > StringVector;

/**
 */
typedef std::vector< unsigned int > UIntVector;

/**
 */
typedef std::list< std::string > StringList;

/**
 */
typedef std::vector< double > DoubleVector;

/*******************************************************************************/
/* Type definitions of ITK realization.                                        */

/**
 */
typedef itk::Array< double > ParametersType;

/*******************************************************************************/
/* Type definitions depending on dimension.                                    */

/**
 */
typedef itk::ImageRegion< Monteverdi2_DIMENSION > ImageRegionType;

/**
 */
typedef itk::Index< Monteverdi2_DIMENSION > IndexType;

/**
 */
typedef itk::Size< Monteverdi2_DIMENSION > SizeType;

/**
 */
typedef itk::ImageBase< Monteverdi2_DIMENSION > ImageBaseType;

/*******************************************************************************/
/* Type definitions for scalar/mono-band images.                               */

/**
 */
typedef
otb::Image< ComponentType, Monteverdi2_DIMENSION >
ScalarImageType;

/**
 */
typedef
otb::ImageFileReader< ScalarImageType > ScalarImageFileReaderType;

/**
 */
typedef
otb::ImageFileWriter< ScalarImageType > ScalarImageFileWriterType;

/*******************************************************************************/
/* Type definitions for vector/multi-band images (generic internal data).      */

/**
 */
typedef
otb::VectorImage< ComponentType, Monteverdi2_DIMENSION >
VectorImageType;

/**
 */
typedef otb::ImageFileReader< VectorImageType > VectorImageFileReaderType;

/**
 */
typedef otb::ImageFileWriter< VectorImageType > VectorImageFileWriterType;

/**
 */
typedef VectorImageType::SpacingType SpacingType;

/**
 */
typedef VectorImageType::SizeType SizeType;

/**
 */
typedef VectorImageType::PointType PointType;

/*******************************************************************************/
/* Type definitions for application defaults.                                  */

/**
 */
typedef mvd::VectorImageType DefaultImageType;

/**
 */
typedef mvd::VectorImageFileReaderType DefaultImageFileReaderType;

/**
 */
struct PixelInfo
{
  typedef std::vector< PixelInfo > Vector;

  PixelInfo() :
    m_Key(),
    m_Point(),
    m_Index(),
    m_Pixel(),
    m_HasPoint( false ),
    m_HasIndex( false ),
    m_HasPixel( false )
  {
  }

  std::string m_Key;

  DefaultImageType::PointType m_Point;
  DefaultImageType::IndexType m_Index;
  DefaultImageType::PixelType m_Pixel;

  bool m_HasPoint: 1;
  bool m_HasIndex: 1;
  bool m_HasPixel: 1;
};

/*******************************************************************************/
/* Type definitions for wrapped applications                                   */

/**
 */
typedef std::map< std::string, std::string > ApplicationDocNameToNameMap;

/**
 */
typedef std::map< std::string, StringVector > ApplicationsTagContainer;

/*******************************************************************************/
/* Type definitions for dataset properties                                     */
/**
 */
typedef qlonglong SqlId;
/**
 */
// typedef SqlId DatasetId;
typedef QString DatasetHash;
/**
 */
typedef std::pair< std::string, std::string > PropertyType;

/**
 */
typedef std::vector< PropertyType > PropertiesVector;

/**
 */
typedef
std::pair< std::string, std::vector< PropertyType > > PropertiesVectorByCategory;

/**
 */
typedef std::map< std::string, PropertiesVector > PropertiesContainer;

/*******************************************************************************/
/* Type definitions for Dataset list                                           */

/**
 */
typedef QPair< QString, QString > StringPairType;

/**
 */
typedef QList< StringPairType > StringPairListType;

/*******************************************************************************/
template< typename T >
inline
T
QObjectCast( QObject * object, const QString & string = QString() )
{
  T model = qobject_cast< T >( object );

  if( model!=object )
    {
    if( !string.isNull() )
      qWarning() << string;

    throw std::bad_cast();
    }

  return model;
}

/*******************************************************************************/
} // end namespace 'mvd'

#endif // __mvdTypes_h
