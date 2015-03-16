/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "mvdQuicklookViewRenderer.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtOpenGL>

//
// System includes (sorted by alphabetic order)
// necessary for the opengl variables and methods

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)
#include "otbGlImageActor.h"

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdDatasetModel.h"
#include "Core/mvdStackedLayerModel.h"
#include "Core/mvdTypes.h"
#include "Core/mvdVectorImageModel.h"

namespace mvd
{
/*
  TRANSLATOR mvd::QuicklookViewRenderer

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */
/*****************************************************************************/
QuicklookViewRenderer
::QuicklookViewRenderer( QObject* parent ) :
  ImageViewRenderer( parent ),
  m_GlRoiActor( otb::GlROIActor::New() )
{
  assert( !m_GlRoiActor.IsNull() );
  this->SetReferenceActorShaderMode("STANDARD");
}

/*****************************************************************************/
QuicklookViewRenderer
::~QuicklookViewRenderer()
{
}

/*****************************************************************************/
AbstractImageViewRenderer::RenderingContext*
QuicklookViewRenderer
::NewRenderingContext() const
{
  RenderingContext* context = new QuicklookViewRenderer::RenderingContext();

#if USE_VIEW_SETTINGS_SIDE_EFFECT
#else
  assert( !m_GlView.IsNull() );

  //
  // Share otb::GlViewRendering settings with manipulator using
  // RenderingContext. Manipulator can then setup otb::ViewSettings
  // directly by side-effect.
  context->m_ViewSettings = m_GlView->GetSettings();
#endif

  return context;
}

/*******************************************************************************/
void
QuicklookViewRenderer
::virtual_SetProjection()
{
  SetWktAndKwl();
}

/*******************************************************************************/
void
QuicklookViewRenderer
::virtual_UpdateProjection()
{
  SetWktAndKwl();
}

/*******************************************************************************/
void
QuicklookViewRenderer
::SetWktAndKwl()
{
  // qDebug() << this << "::SetWktAndKwl()";

  assert( GetLayerStack()!=NULL );

  if( GetLayerStack()->IsEmpty() )
    return;

  otb::GlImageActor::Pointer referenceGlImageActor(
    GetReferenceActor< otb::GlImageActor >()
  );

  assert( !referenceGlImageActor.IsNull() );

  m_GlRoiActor->SetKwl( referenceGlImageActor->GetKwl() );
  m_GlRoiActor->SetWkt( referenceGlImageActor->GetWkt() );
}

/*******************************************************************************/
void
QuicklookViewRenderer
::virtual_FinishScene()
{
  // qDebug() << this << "::virtual_FinishScene()";

  assert( !m_GlView.IsNull() );


  std::string key( m_GlView->AddActor( m_GlRoiActor ) );

  m_GlRoiActor->SetVisible( true );

  // qDebug() << "Added roi-actor:" << FromStdString( key );

  /*
  ColorType color;

  color.Fill( 1.0 );

  m_GlRoiActor->SetColor( color ); 
  */
  m_GlRoiActor->SetFill( false );
  m_GlRoiActor->SetAlpha( 0.2 );

  m_GlView->MoveActorToEndOfRenderingOrder( key, true );

#if 0
  otb::GlImageActor::Pointer referenceGlImageActor(
    GetReferenceActor< otb::GlImageActor >()
  );

  if( referenceGlImageActor.IsNull() )
    return;

  m_GlRoiActor->SetKwl( referenceGlImageActor->GetKwl() );
  m_GlRoiActor->SetWkt( referenceGlImageActor->GetWkt() );
#endif
}

/*****************************************************************************/
void
QuicklookViewRenderer
::UpdateActors( const AbstractImageViewRenderer::RenderingContext* c )
{
  // qDebug() << this << "::UpdateActors()";

  assert( c!=NULL );

  ImageViewRenderer::UpdateActors( c );

  assert(
    c==dynamic_cast< const QuicklookViewRenderer::RenderingContext * >( c )
  );

  const QuicklookViewRenderer::RenderingContext * context =
    dynamic_cast< const QuicklookViewRenderer::RenderingContext * >( c );

  /*
  qDebug()
    << "ROI-origin:"
    << context->m_RoiOrigin[ 0 ] << "," << context->m_RoiOrigin[ 1 ]
    << "ROI-extent:"
    << context->m_RoiExtent[ 0 ] << "," << context->m_RoiExtent[ 1 ];
  */

  m_GlRoiActor->SetUL( context->m_RoiOrigin );
  m_GlRoiActor->SetLR( context->m_RoiExtent );
}

/*****************************************************************************/
/* SLOTS                                                                     */
/*****************************************************************************/

} // end namespace 'mvd'
