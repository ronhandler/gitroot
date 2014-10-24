//package com.ron.proj;

//import java.lang.*;

class Main
{
	public static void main(String args[])
	{
		Conf conf = new Conf();
		conf.loadConfig("./config.txt");
		System.out.println("Reading values from config:");
		System.out.println(conf.getVal("str"));
		System.out.println(conf.getVal("width") + "x" + conf.getVal("height"));
	}
}

