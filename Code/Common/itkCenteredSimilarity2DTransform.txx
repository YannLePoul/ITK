/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkCenteredSimilarity2DTransform.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkCenteredSimilarity2DTransform_txx
#define _itkCenteredSimilarity2DTransform_txx

#include "itkCenteredSimilarity2DTransform.h"


namespace itk
{

// Constructor with default arguments
template <class TScalarType>
CenteredSimilarity2DTransform<TScalarType>
::CenteredSimilarity2DTransform():Superclass()
{
}



// Copy Constructor
template <class TScalarType>
CenteredSimilarity2DTransform<TScalarType>
::CenteredSimilarity2DTransform( const Self & other ):Superclass( other )
{
}


// Set Parameters
template <class TScalarType>
void
CenteredSimilarity2DTransform<TScalarType>
::SetParameters( const ParametersType & parameters )
{
  itkDebugMacro( << "Setting paramaters " << parameters );

  // Set angles with parameters
  this->SetScale(parameters[0]);
 
  // Set angles with parameters
  this->SetAngle( parameters[1] );

  InputPointType center;
  for(unsigned int j=0; j < SpaceDimension; j++) 
    {
    center[j] = parameters[j+2];
    }
  this->SetCenter( center );


  // Transfer the translation part
  OffsetType translation;
  for(unsigned int i=0; i < SpaceDimension; i++) 
    {
    translation[i] = parameters[i+4];
    }

  this->SetTranslation( translation );

  this->ComputeMatrixAndOffset();

  itkDebugMacro(<<"After setting paramaters ");
}


// Get Parameters
template <class TScalarType>
const typename CenteredSimilarity2DTransform<TScalarType>::ParametersType &
CenteredSimilarity2DTransform<TScalarType>
::GetParameters( void ) const
{
  itkDebugMacro( << "Getting parameters ");

  this->m_Parameters[0] = this->GetScale();
  this->m_Parameters[1] = this->GetAngle();
 
  InputPointType center = this->GetCenter();
  for(unsigned int j=0; j < SpaceDimension; j++) 
    {
    this->m_Parameters[j+2] = center[j];
    }

  // Transfer the translation part
  OffsetType translation = this->GetTranslation();
  for(unsigned int i=0; i < SpaceDimension; i++) 
    {
    this->m_Parameters[i+4] = translation[i];
    }

  itkDebugMacro(<<"After getting parameters " << this->m_Parameters );

  return this->m_Parameters;
}

// Set parameters
template<class TScalarType>
const typename CenteredSimilarity2DTransform<TScalarType>::JacobianType &
CenteredSimilarity2DTransform<TScalarType>::
GetJacobian( const InputPointType & p ) const
{

  // need to check if angles are in the right order
  const double angle = this->GetAngle();
  const double ca = cos( angle );
  const double sa = sin( angle );

  this->m_Jacobian.Fill(0.0);

  const InputPointType center = this->GetCenter();  
  const double cx = center[0];
  const double cy = center[1];

  const OutputVectorType translation = this->GetTranslation();

  // derivatives with respect to the scale
  this->m_Jacobian[0][0] =    ca * ( p[0] - cx ) - sa * ( p[1] - cy );
  this->m_Jacobian[1][0] =    sa * ( p[0] - cx ) + ca * ( p[1] - cy ); 

  // derivatives with respect to the angle
  this->m_Jacobian[0][1] = ( -sa * ( p[0] - cx ) - ca * ( p[1] - cy ) ) * this->GetScale();
  this->m_Jacobian[1][1] = (  ca * ( p[0] - cx ) - sa * ( p[1] - cy ) ) * this->GetScale();

  // compute derivatives with respect to the center part
  // first with respect to cx
  this->m_Jacobian[0][2] = 1.0 - ca * this->GetScale();
  this->m_Jacobian[1][2] =     - sa * this->GetScale();
  // then with respect to cy
  this->m_Jacobian[0][3] =       sa * this->GetScale();
  this->m_Jacobian[1][3] = 1.0 - ca * this->GetScale();


  // compute derivatives with respect to the translation part
  // first with respect to tx
  this->m_Jacobian[0][4] = 1.0;
  this->m_Jacobian[1][4] = 0.0;
  // first with respect to ty
  this->m_Jacobian[0][5] = 0.0;
  this->m_Jacobian[1][5] = 1.0;

  return this->m_Jacobian;

}

 
// Print self
template<class TScalarType>
void
CenteredSimilarity2DTransform<TScalarType>::
PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
}

} // namespace

#endif
