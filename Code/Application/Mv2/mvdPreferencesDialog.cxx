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
#include "mvdPreferencesDialog.h"
#include "ui_mvdPreferencesDialog.h"


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
#include "Gui/mvdI18nApplication.h"
#include "Gui/mvdI18nMainWindow.h"

namespace mvd
{
/*
  TRANSLATOR mvd::PreferencesDialog

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
PreferencesDialog
::PreferencesDialog( QWidget* parent, Qt::WindowFlags flags ) :
  QDialog( parent, flags ),
  m_UI( new mvd::Ui::PreferencesDialog() ),
  m_ElevationSetupModified(false),
  m_ResultsDirModified(false)
{
  m_UI->setupUi( this );

  m_UI->settingsGroupBox->setVisible( false );

  m_UI->resultDirPathLineEdit->setText(
    I18nApplication::Instance()->RetrieveSettingsKey(
      I18nCoreApplication::SETTINGS_KEY_RESULTS_DIR
    )
    .toString()
  );

  m_UI->srtmLineEdit->setText(
    I18nApplication::Instance()->RetrieveSettingsKey(
      I18nCoreApplication::SETTINGS_KEY_SRTM_DIR
    )
    .toString()
  );

  m_UI->srtmCheckbox->setChecked(
    I18nApplication::Instance()->RetrieveSettingsKey(
      I18nCoreApplication::SETTINGS_KEY_IS_SRTM_DIR_ACTIVE
    )
    .toBool()
  );
  m_UI->srtmLineEdit->setEnabled( m_UI->srtmCheckbox->isChecked() );
  m_UI->srtmButton->setEnabled( m_UI->srtmCheckbox->isChecked() );

  m_UI->geoidLineEdit->setText(
    I18nApplication::Instance()->RetrieveSettingsKey(
      I18nCoreApplication::SETTINGS_KEY_GEOID_PATH
    )
    .toString()
  );

  m_UI->geoidCheckbox->setChecked(
    I18nApplication::Instance()->RetrieveSettingsKey(
      I18nCoreApplication::SETTINGS_KEY_IS_GEOID_PATH_ACTIVE
    )
    .toBool()
  );

  m_UI->geoidLineEdit->setEnabled( m_UI->geoidCheckbox->isChecked() );
  m_UI->geoidButton->setEnabled( m_UI->geoidCheckbox->isChecked() );

  // Connect centralWidget manipulator to Ql renderer when viewportRegionChanged
  QObject::connect(
    m_UI->buttonBox, SIGNAL( rejected() ), 
    this, SLOT( close() )
    );
}

/*******************************************************************************/
PreferencesDialog
::~PreferencesDialog()
{
  delete m_UI;
  m_UI = NULL;
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/
void
PreferencesDialog
::on_buttonBox_accepted()
{
//
// Code is temporarily disabled (waiting for client approval about
// what to do).
//
// Selecting cache-dir during application run induces GUI and
// DatabaseModel refreshed along with checking consistency of selected
// directory content.
#if 0
  if (m_CacheDirRootModified)
    {
    // Create the cache dir
    I18nApplication::Instance()->MakeCacheDir(m_CacheDirRoot);

    // Save the cache directory into the settings file
    I18nApplication::Instance()->WriteCacheDirIntoSettings();
    }
#endif

  if( m_ResultsDirModified )
    {
    // Set the result dir
    I18nApplication::Instance()->StoreSettingsKey(
      I18nCoreApplication::SETTINGS_KEY_RESULTS_DIR,
      QDir::cleanPath( m_UI->resultDirPathLineEdit->text()
      )
    );
   
    m_ResultsDirModified = false;
    }

  I18nApplication::Instance()->StoreSettingsKey(
    I18nCoreApplication::SETTINGS_KEY_SRTM_DIR,
    QDir::cleanPath( m_UI->srtmLineEdit->text()
    )
  );
  I18nApplication::Instance()->StoreSettingsKey(
    I18nCoreApplication::SETTINGS_KEY_GEOID_PATH,
    m_UI->geoidLineEdit->text()
  );
  I18nApplication::Instance()->StoreSettingsKey(
    I18nCoreApplication::SETTINGS_KEY_IS_SRTM_DIR_ACTIVE,
    this->m_UI->srtmCheckbox->isChecked()
  );
  I18nApplication::Instance()->StoreSettingsKey(
    I18nCoreApplication::SETTINGS_KEY_IS_GEOID_PATH_ACTIVE,
    this->m_UI->geoidCheckbox->isChecked()
  );

  if( m_ElevationSetupModified )
    {
    I18nApplication::Instance()->ElevationSetup();

    m_ElevationSetupModified = false;
    }

  close();
}

/*******************************************************************************/
void PreferencesDialog
::on_srtmCheckbox_clicked()
{
  this->m_UI->srtmLineEdit->setEnabled(this->m_UI->srtmCheckbox->isChecked());
  this->m_UI->srtmButton->setEnabled(this->m_UI->srtmCheckbox->isChecked());
  m_ElevationSetupModified = true;
}

void PreferencesDialog
::on_geoidCheckbox_clicked()
{
  this->m_UI->geoidLineEdit->setEnabled(this->m_UI->geoidCheckbox->isChecked());
  this->m_UI->geoidButton->setEnabled(this->m_UI->geoidCheckbox->isChecked());
  m_ElevationSetupModified = true;
}


void PreferencesDialog
::on_srtmButton_clicked()
{
  while (true)
    {
    QString srtmDirStr = I18nMainWindow::GetExistingDirectory(
        this,
        tr("Select the directory containing DEM files."));
    if (srtmDirStr.isEmpty())
      { // User push default button => don't modify the value
      break;
      }
    else
      { // User select something, test if it is correct
        QDir displayedDir (srtmDirStr);
        m_UI->srtmLineEdit->setText(displayedDir.absolutePath());
        m_ElevationSetupModified = true;
        break;
      }
    }
}


void PreferencesDialog
::on_geoidButton_clicked()
{
  while (true)
    {
    QString geoidStr = I18nMainWindow::GetOpenFileName(
        this,
        tr("Select a geoid file."));
    if (geoidStr.isEmpty())
      { // User push default button => don't modify the value
      break;
      }
    else
      { // User select something, test if it is correct
        QDir displayedDir (geoidStr);
        m_UI->geoidLineEdit->setText(displayedDir.absolutePath());
        m_ElevationSetupModified = true;
        break;
      }
    }
}


void PreferencesDialog
::on_resultDirButton_clicked()
{
  while (true)
    {
    QString resultsDirStr = I18nMainWindow::GetExistingDirectory(
        this,
        tr("Select the default directory for results data: "));
    if (resultsDirStr.isEmpty())
      { // User push default button => don't modify the value
      break;
      }
    else
      { // User select something, test if it is correct
        QDir displayedDir (resultsDirStr);
        m_UI->resultDirPathLineEdit->setText(displayedDir.absolutePath());
        m_ResultsDirModified = true;
        break;
      }
    }
}


/*******************************************************************************/

} // end namespace 'mvd'
