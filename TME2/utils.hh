template<typename iterator>
size_t count (iterator begin, iterator end) {
	size_t i = 0;
	for (;begin != end;begin++) {
		i++;
	}
	return i;
}

template<typename iterator,typename T>
size_t count_if_equal (iterator begin, iterator end, const T & val) {
	size_t i = 0;
	for (;begin != end;begin++) {
		if (*begin == val)
			i++;
	}
	return i;

}