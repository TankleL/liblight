/*******************************************************************************
@module node component

==----------------------------------------------------------------------------==

MIT License

Copyright (c) 2018 Tankle L.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#pragma once

#include "prerequisites.hpp"

namespace Light
{
	/************************************************************************/
	/*                              DECLARATION                             */
	/************************************************************************/
	class LIGHT_API INodeComponentBehavior
	{
	public:
		virtual void update() = 0;
		virtual void reset() = 0;
	};

	class Node;
	class LIGHT_API NodeComponent : public INodeComponentBehavior
	{
	public:
		NodeComponent();
		virtual ~NodeComponent();

	public:
	protected:
		std::string	m_name;
		Node*		m_holder;	// the node handling this component. 
	};

	/************************************************************************/
	/*                               DEFINITION                             */
	/************************************************************************/
	inline NodeComponent::NodeComponent()
		: m_holder(nullptr)
	{}

	inline NodeComponent::~NodeComponent()
	{}
}
