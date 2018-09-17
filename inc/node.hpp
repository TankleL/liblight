/*******************************************************************************
@module node for rendering.

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
#include "node-component.hpp"

namespace Light
{
	/************************************************************************/
	/*                              DECLARATION                             */
	/************************************************************************/
	class LIGHT_API Node
	{
	public:
		Node(const std::string& name);
		virtual ~Node();

	public:	// as a parent.
		/**
		 * @brief create a new child node object and manage it.
		 * the child will be released from memory when this parent
		 * is releasing.
		 *
		 * @retval a point to created child node. do not manage it
		 * until you called detach_child() method.
		 */
		Node* create_child(const std::string& name);

		/**
		 * @brief add a child create by other parent node. the child
		 * must detach from it's parent before you call this method.
		 *
		 * @param other_node_child - a pointer to the child.
		 */
		void add_child(Node* other_node_child);

		/**
		 * @brief remove a child in this node and release it from memory
		 * immediately.
		 *
		 * @param child_name.
		 */
		void remove_child(const std::string& child_name);

		/**
		 * @brief detach a child from this node. you have to manage it's
		 * life-cycle manually.
		 */
		Node* detach_child(const std::string& child_name);

	public:	// as a child
		/**
		 * @brief detach from parent. you have to manage this node's life-
		 * cycle manually.
		 */
		void detach();

	public: // as a node
		/**
		* @brief get the name of this node
		*/
		std::string get_name() const;

		void add_component(
			const std::string& name,
			const std::shared_ptr<NodeComponent>& component);

	protected:
		typedef std::unordered_map<std::string, Node*>
			CHILD_CONTAINER_T;
		typedef std::unordered_map<std::string,
			std::shared_ptr<NodeComponent>>
			COM_CONTAINER_T;

	protected:
		CHILD_CONTAINER_T	m_children;
		COM_CONTAINER_T		m_coms;
		std::string			m_name;
		Node*				m_parent;
	};


	/************************************************************************/
	/*                              DEFINITION                              */
	/************************************************************************/
	inline Node::Node(const std::string& name)
		: m_name(name)
		, m_parent(nullptr)
	{}

	inline Node::~Node()
	{
		for (CHILD_CONTAINER_T::iterator iter = m_children.begin();
			iter != m_children.end();
			++iter)
			if (iter->second)
				delete (iter->second);
	}

	inline Node* Node::create_child(const std::string& name)
	{
		assert(m_children[name] == NULL);
		Node* cn = new Node(name);
		cn->m_parent = this;
		m_children[name] = cn;
		return cn;
	}

	inline void Node::add_child(Node* other_node_child)
	{
		assert(other_node_child->m_parent == nullptr);
		assert(m_children[other_node_child->get_name()] == nullptr);
		m_children[other_node_child->get_name()] = other_node_child;
		other_node_child->m_parent = this;
	}

	inline void Node::remove_child(const std::string& child_name)
	{
		CHILD_CONTAINER_T::iterator child = m_children.find(child_name);
		if (child != m_children.end())
		{
			if(child->second)
				delete child->second;
			m_children.erase(child);
		}
	}

	inline Node* Node::detach_child(const std::string& child_name)
	{
		Node* res = nullptr;
		CHILD_CONTAINER_T::iterator child = m_children.find(child_name);
		if (child != m_children.end())
		{
			res = child->second;
			child->second->m_parent = nullptr;
			m_children.erase(child);
		}
		return res;
	}
	
	inline void Node::detach()
	{
		assert(m_parent);
		m_parent->detach_child(get_name());
	}

	inline std::string Node::get_name() const
	{
		return m_name;
	}

	inline void Node::add_component(
		const std::string& name,
		const std::shared_ptr<NodeComponent>& component)
	{
		m_coms[name] = component;
	}
}
