/* ****************************************************************************
@module tree
-------------------------------------------------------------------------------

Copyright (c) 2018, Tain L.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**************************************************************************** */

#pragma once

namespace Light
{
	template<typename _KeyType, typename _ValueType>
	class XTree
	{
	public:
		typedef XTree<_KeyType, _ValueType>	node_t;
	
	public:
		XTree()
		{}

		XTree(const _KeyType& key)
			: m_key(key)
		{}

		XTree(const _KeyType& key, const _ValueType& value)
			: m_key(key)
			, m_value(value)
		{}

		XTree(const XTree<_KeyType, _ValueType>& rhs)
			: m_key(rhs.m_key)
			, m_value(rhs.m_value)
			, m_children(rhs.m_children)
		{}

		XTree(XTree<_KeyType, _ValueType>&& rhs)
			: m_key(rhs.m_key)
			, m_value(rhs.m_value)
			, m_children(rhs.m_children)
		{}

		XTree& operator=(const XTree<_KeyType, _ValueType>& rhs)
		{
			m_key = rhs.m_key;
			m_value = rhs.m_value;
			m_children = rhs.m_children;
			return *this;
		}

		XTree& operator=(XTree<_KeyType, _ValueType>&& rhs)
		{
			m_key = rhs.m_key;
			m_value = rhs.m_value;
			m_children = rhs.m_children;
			return *this;
		}

		bool operator==(const XTree<_KeyType, _ValueType>& rhs) const
		{
			return m_key == rhs.m_key;
		}

	public:
		node_t& get_child_ref(const _KeyType& key)
		{
			return m_children.at(key);
		}

		void push(const XTree<_KeyType, _ValueType>& tree)
		{
			m_children[tree.get_key()] = tree;
		}

		void remove(const _KeyType& key)
		{
			auto iter = m_children.find(key);
			if (iter != m_children.end())
			{
				m_children.erase(iter);
			}
		}

		_KeyType get_key() const
		{
			return m_key;
		}

		void set_value(const _ValueType& value)
		{
			m_value = value;
		}

		_ValueType get_value() const
		{
			return m_value;
		}

	protected:
		std::unordered_map<_KeyType, node_t>	m_children;
		_KeyType			m_key;
		_ValueType			m_value;
	};
}