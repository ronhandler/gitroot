//package com.ron.proj;

import java.lang.*;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;

class Main
{
	public static void powerset(List<Integer> list)
	{
		for (int i=0; i<Math.pow(2,list.size()); ++i) {
			System.out.printf("{ ");
			int binary = i;
			boolean first = true;
			for (int j=0; j<list.size(); ++j) {
				if (1 == binary%2) {
					if (first) {
						System.out.printf("%d", list.get(j));
						first = false;
					} else {
						System.out.printf(", %d", list.get(j));
					}
				}
				binary = binary/2;
			}
			System.out.printf(" }\n");
		}
	}

	public static void main(String args[])
	{
		System.out.println("hello world");
		List<Integer> list = new ArrayList<Integer>();
		list.add(1);
		list.add(2);
		list.add(3);
		list.add(4);
		list.add(5);
		powerset(list);
	}
}

