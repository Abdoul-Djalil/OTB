/*=========================================================================

  Program:   Monteverdi
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "mvdAbstractDragAndDropEventFilter.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)

namespace mvd
{

/*
  TRANSLATOR mvd::AbstractDragAndDropEventFilter

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
AbstractDragAndDropEventFilter
::AbstractDragAndDropEventFilter( QObject* p  ) :
  QObject( p )
{
}

/*****************************************************************************/
AbstractDragAndDropEventFilter
::~AbstractDragAndDropEventFilter()
{
}

/*****************************************************************************/
bool
AbstractDragAndDropEventFilter
::eventFilter( QObject* object, QEvent* event )
{
  switch( event->type() )
    {
    case QEvent::DragEnter:
      return DragEnterEvent( object, dynamic_cast< QDragEnterEvent* >( event ) );
      break;

    case QEvent::DragMove:
      return DragMoveEvent( object, dynamic_cast< QDragMoveEvent* >( event ) );
      break;

    case QEvent::DragLeave:
      return DragLeaveEvent( object, dynamic_cast< QDragLeaveEvent* >( event ) );
      break;

    case QEvent::Drop:
      return DropEvent( object, dynamic_cast< QDropEvent* >( event ) );
      break;

    default:
      break;
    }

  return QObject::eventFilter( object, event );
}

/*****************************************************************************/
/* SLOTS                                                                     */
/*****************************************************************************/

} // end namespace 'mvd'
