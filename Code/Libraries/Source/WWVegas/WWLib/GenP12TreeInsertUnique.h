#pragma once
// Retail hinted insertion shared by the tree owner and its map caller.
typedef _STL::pair<const Gen_p12pod, int> GenP12Pair;
typedef _STL::_Rb_tree<Gen_p12pod, GenP12Pair,
	_STL::_Select1st<GenP12Pair>, _STL::less<Gen_p12pod>,
	_STL::allocator<GenP12Pair> > GenP12Tree;

template <>
inline GenP12Tree::iterator GenP12Tree::insert_unique(
	GenP12Tree::iterator __position, const GenP12Pair &__v)
{
	if (__position._M_node == this->_M_header._M_data->_M_left) {
		if (size() <= 0)
			return insert_unique(__v).first;

		if (_M_key_compare(_STL::_Select1st<GenP12Pair>()(__v),
			_S_key(__position._M_node)))
			return _M_insert(__position._M_node, __position._M_node, __v);
		else {
			bool __comp_pos_v = _M_key_compare(
				_S_key(__position._M_node), _STL::_Select1st<GenP12Pair>()(__v));
			if (__comp_pos_v == false)
				return __position;
			iterator __after = __position;
			++__after;
			if (__after._M_node == this->_M_header._M_data)
				return _M_insert(0, __position._M_node, __v, __position._M_node);
			if (_M_key_compare(_STL::_Select1st<GenP12Pair>()(__v),
				_S_key(__after._M_node))) {
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v, __position._M_node);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			} else
				return insert_unique(__v).first;
		}
	} else if (__position._M_node == this->_M_header._M_data) {
		if (_M_key_compare(_S_key(_M_rightmost()),
			_STL::_Select1st<GenP12Pair>()(__v)))
			return _M_insert(0, _M_rightmost(), __v, __position._M_node);
		else
			return insert_unique(__v).first;
	} else {
		iterator __before = __position;
		--__before;
		bool __comp_pos_v = false;
		bool __comp_v_pos = _M_key_compare(
			_STL::_Select1st<GenP12Pair>()(__v), _S_key(__position._M_node));
		if (__comp_v_pos
			&& _M_key_compare(_S_key(__before._M_node),
				_STL::_Select1st<GenP12Pair>()(__v))) {
			if (_S_right(__before._M_node) == 0)
				return _M_insert(0, __before._M_node, __v, __before._M_node);
			else
				return _M_insert(__position._M_node, __position._M_node, __v);
		} else {
			iterator __after = __position;
			++__after;
			__comp_pos_v = __comp_v_pos;
			__comp_pos_v = !__comp_pos_v;
			if (!__comp_v_pos)
				__comp_pos_v = _M_key_compare(
					_S_key(__position._M_node),
					_STL::_Select1st<GenP12Pair>()(__v));
			if (!__comp_v_pos && __comp_pos_v
				&& (__after._M_node == this->_M_header._M_data
					|| _M_key_compare(_STL::_Select1st<GenP12Pair>()(__v),
						_S_key(__after._M_node)))) {
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v, __position._M_node);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			} else {
				if (__comp_v_pos == __comp_pos_v)
					return __position;
				else
					return insert_unique(__v).first;
			}
		}
	}
}

