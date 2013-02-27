public class bittest {

	public static void test() {
		final int N = 3200000;
		int[] array = new int[N];
		java.util.Random r = new java.util.Random();
		for (int k = 0; k < N; ++k) {
			array[k] = r.nextInt();
		}
		int bogusxor = 0;
		int bogussum = 0;
		int count1 = 0, count2 = 0;
		long bef1 = System.currentTimeMillis();
		for (int k = 0; k < N; ++k) {
			if ((array[k] & (1 << 31)) != 0)
				bogussum += array[k] ^ (1 << 31);
			else
				bogusxor ^= array[k];
		}
		long aft1 = System.currentTimeMillis();
		long bef2 = System.currentTimeMillis();

		for (int k = 0; k < N / 32; ++k) {
			/*
			 * for(int L = 0; L<31; ++L) { if((array[k*32] & (1<<L) )!=0)
			 * bogussum += array[k*32+L+1] ^ (1<<31); else bogusxor ^=
			 * array[k*32+L+1]; }
			 */
			int L;
			L = 0;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 1;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 2;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 3;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 4;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 5;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 6;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 7;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 8;

			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 9;

			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 10;

			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 11;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 12;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 13;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 14;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 15;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 16;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 17;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 18;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 19;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 20;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 21;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 22;

			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 23;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 24;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 25;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 26;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 27;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 28;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 29;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];
			L = 30;
			if ((array[k * 32] & (1 << L)) != 0)
				bogussum += array[k * 32 + L + 1] ^ (1 << 31);
			else
				bogusxor ^= array[k * 32 + L + 1];

		}
		long aft2 = System.currentTimeMillis();
		System.out.println(aft1 - bef1);
		System.out.println(aft2 - bef2);

		System.out.println(bogusxor + bogussum);

	}

	public static void main(String[] args) {
		test();
		test();
		test();
		test();
	}

}
