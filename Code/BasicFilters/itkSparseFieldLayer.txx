/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkSparseFieldLayer.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkSparseFieldLayer_txx
#define __itkSparseFieldLayer_txx

namespace itk {

template<class TNodeType>
SparseFieldLayer<TNodeType>
::SparseFieldLayer()
{
  m_HeadNode = new NodeType;
  m_HeadNode->Next = m_HeadNode;
  m_HeadNode->Previous = m_HeadNode;
}

template<class TNodeType>
SparseFieldLayer<TNodeType>
::~SparseFieldLayer()
{
  delete m_HeadNode;
}
  
template<class TNodeType>
void
SparseFieldLayer<TNodeType>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
  
  os << indent << "m_HeadNode:  " << m_HeadNode << std::endl;
  os << indent << "Empty? : " << this->Empty() << std::endl;
}

template<class TNodeType>
unsigned int
SparseFieldLayer<TNodeType>
::Size() const
{
  unsigned int counter = 0;

  for (NodeType *it = m_HeadNode; it->Next != m_HeadNode; it = it->Next)
    { counter++; }
  return counter;
}

}// end namespace itk

#endif
