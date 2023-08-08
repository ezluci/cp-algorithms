template<typename T>
struct biset {
	const int BISET_BITS_PER_WORD = 8 * sizeof(T);
	int b, n;
	vector<T> bits;
	biset() {}
	biset(int b): b(b) {
		init(b);
	}
	void init(int b) {
		n = (b + BISET_BITS_PER_WORD - 1) / BISET_BITS_PER_WORD;
		bits.assign(n, 0);
	}
	void clear() {
		b = n = 0;
		bits.clear();
	}
	void reset() {
		bits.assign(n, 0);
	}
	void clean() {
		if(b != BISET_BITS_PER_WORD * n) {
			bits.back() &= (T(1) << (b - BISET_BITS_PER_WORD * (n - 1))) - 1;
		}
	}
	bool get(int idx) const {
		return bits[idx / BISET_BITS_PER_WORD] >> (idx % BISET_BITS_PER_WORD) & 1;
	}
	bool operator [] (int idx) const {
		return get(idx);
	}
	void set(int idx, bool val) {
		bits[idx / BISET_BITS_PER_WORD] &= ~(T(1) << (idx % BISET_BITS_PER_WORD));
		bits[idx / BISET_BITS_PER_WORD] |= T(1) << (idx % BISET_BITS_PER_WORD);
	}
	biset& operator &= (const biset &oth) {
		for(int i = 0; i < n; i++) {
			bits[i] &= oth.bits[i];
		}
		return *this;
	}
	biset operator & (const biset &oth) {
		biset res = *this;
		res &= oth;
		return res;
	}
	biset& operator |= (const biset &oth) {
		for(int i = 0; i < n; i++) {
			bits[i] |= oth.bits[i];
		}
		return *this;
	}
	biset operator | (const biset &oth) {
		biset res = *this;
		res |= oth;
		return res;
	}
	biset& operator <<= (int shift) {
		const int wshift = shift / BISET_BITS_PER_WORD;
		const int offset = shift % BISET_BITS_PER_WORD;
		if(offset == 0) {
			for(int i = n - 1; i >= wshift; i--) {
				bits[i] = bits[i - wshift];
			}
		} else {
			const int sub_offset = BISET_BITS_PER_WORD - offset;
			for(int  i = n - 1; i > wshift; i--) {
				bits[i] = ((bits[i - wshift] << offset) | bits[i - wshift - 1] >> sub_offset);
			}
			bits[wshift] = bits[0] << offset;
		}
		fill(bits.begin(), bits.begin() + wshift, static_cast<T>(0));
		return *this;
	}
	biset operator << (int shift) {
		biset res = *this;
		res <<= shift;
		return res;
	}
	biset& or_left_shift(int shift) {
		const int wshift = shift / BISET_BITS_PER_WORD;
		const int offset = shift % BISET_BITS_PER_WORD;
		if(offset == 0) {
			for(int i = n - 1; i >= wshift; i--) {
				bits[i] |= bits[i - wshift];
			}
		} else {
			const int sub_offset = BISET_BITS_PER_WORD - offset;
			for(int  i = n - 1; i > wshift; i--) {
				bits[i] |= ((bits[i - wshift] << offset) | bits[i - wshift - 1] >> sub_offset);
			}
			bits[wshift] |= bits[0] << offset;
		}
		return *this;
	}
	biset& operator >>= (int shift) {
		const int wshift = shift / BISET_BITS_PER_WORD;
		const int offset = shift % BISET_BITS_PER_WORD;
		const int limit = n - wshift - 1;
		if(offset == 0) {
			for(int i = 0; i <= limit; i++) {
				bits[i] = bits[i + wshift];
			}
		} else {
			const int sub_offset = BISET_BITS_PER_WORD - offset;
			for(int i = 0; i < limit; i++) {
				bits[i] = ((bits[i + wshift] >> offset) | (bits[i + wshift + 1] << sub_offset));
			}
			bits[limit] = bits[n - 1] >> offset;
		}
		fill(bits.begin() + limit + 1, bits.end(), static_cast<T>(0));
		return *this;
	}
	biset& or_right_shift (int shift) {
		const int wshift = shift / BISET_BITS_PER_WORD;
		const int offset = shift % BISET_BITS_PER_WORD;
		const int limit = n - wshift - 1;
		if(offset == 0) {
			for(int i = 0; i <= limit; i++) {
				bits[i] |= bits[i + wshift];
			}
		} else {
			const int sub_offset = BISET_BITS_PER_WORD - offset;
			for(int i = 0; i < limit; i++) {
				bits[i] |= ((bits[i + wshift] >> offset) | (bits[i + wshift + 1] << sub_offset));
			}
			bits[limit] |= bits[n - 1] >> offset;
		}
		return *this;
	}
	biset operator >> (int shift) {
		biset res = *this;
		res >>= shift;
		return res;
	}
	// TODO: count(), _Find_first(), _Find_next()
};
