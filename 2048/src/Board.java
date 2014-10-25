//package proj;

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Random;

class Board
{
	protected int arr[][];
	protected int width;
	protected int height;
	protected static int CHANCE = 50;
	protected Conf conf;
	public Board()
	{
		// Load configuration from config.txt.
 		conf = new Conf();
		conf.loadConfig("./config.txt");
		try {
			width = Integer.parseInt(conf.getVal("width"));
			height = Integer.parseInt(conf.getVal("height"));
		} catch(NumberFormatException e) {
			System.err.println("Error: Expected integer values for dimensions: " + e.toString());
			System.exit(1);
		}
		// Resize the board to match width x height.
		arr = new int[width][height];
		// Init the board.
		for (int y=0; y<height; ++y) {
			for (int x=0; x<width; ++x) {
				arr[x][y]=0;
			}
		}
		// Put some random pieces on the board.
		for (int x=0; x<width; ++x) {
			arr[x][0] = (rand(0,100) > CHANCE) ? 1 : 0;
		}
		arr[2][2] = -1;

	}
	// This is the game loop.
	public void loop()
	{
		boolean running=true;
		while(running) {
			// Clear screen. It's an ugly hack, but oh well...
			cls();
			// Print the board.
			print();
			// Try to get input from the user.
			try {
				BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
				String str = br.readLine().toLowerCase();
				switch (str) {
					case "quit":
					case "q":
						running=false;
						break;
					case "i":
						move(Direction.UP);
						break;
					case "j":
						move(Direction.LEFT);
						break;
					case "k":
						move(Direction.DOWN);
						break;
					case "l":
						move(Direction.RIGHT);
						break;
				}
			} catch(IOException e) {
				running=false;
			}
		}
	}
	private void move(Direction dir)
	{
		// Rotate board in the right direction.
		switch (dir) {
			case UP:
				break;
			case DOWN:
				rotate90d();
				rotate90d();
				break;
			case LEFT:
				rotate90d();
				break;
			case RIGHT:
				rotate90d();
				rotate90d();
				rotate90d();
				break;
		}

		// Push pieces.
		for (int y=0; y<height; ++y) {
			for (int x=0; x<width; ++x) {
				push(x,y);
			}
		}
		// Put some random pieces on the board.
		for (int x=0; x<width; ++x) {
			if (arr[x][height-1] == 0)
				arr[x][height-1] = (rand(0,100) > CHANCE) ? 1 : 0;
		}

		// Rotate board back to original.
		switch (dir) {
			case UP:
				break;
			case DOWN:
				rotate90d();
				rotate90d();
				break;
			case LEFT:
				rotate90d();
				rotate90d();
				rotate90d();
				break;
			case RIGHT:
				rotate90d();
				break;
		}
	}

	private void push(int x, int y)
	{
		if (y == 0)
			return;
		if (arr[x][y] == -1)
			return;
		if (arr[x][y-1] == 0) {
			arr[x][y-1] = arr[x][y];
			arr[x][y] = 0;
		} else
		if (arr[x][y-1] == arr[x][y]) {
			arr[x][y-1]++;
			arr[x][y] = 0;
		}
		push(x,y-1);
	}

	// Clock-wise rotation by 90 degrees.
	private void rotate90d()
	{
		int old_arr[][] = arr;
		arr = new int[height][width];

		// Transpose.
		for (int y=0; y<height; ++y) {
			for (int x=0; x<width; ++x) {
				arr[y][x] = old_arr[x][y];
			}
		}

		// Swap width and height.
		int temp = height;
		height = width;
		width = temp;

		// Reverse each row.
		for (int y=0; y<height; ++y) {
			for (int x=0; x<width/2; ++x) {
				int i=arr[x][y];
				arr[x][y] = arr[width-x-1][y];
				arr[width-x-1][y] = i;
			}
		}
		old_arr = null;
	}
	private void print()
	{
		System.out.println("2048 on a " + width + "x" + height + " board.\n");
		for (int y=0; y<height; ++y) {
			for (int x=0; x<width; ++x) {
				//System.out.print(".");
				if (arr[x][y] == -1)
					System.out.format("   X ", arr[x][y]); 
				else
					System.out.format("%4d ", arr[x][y]); 
			}
			System.out.print("\n");
		}
		System.out.println("\nTo move, hit i,j,k or l, followed by RETURN. Hit q to quit.");
		System.out.print("Your choice:  ");

	}
	private void cls()
	{
		System.out.print("\n\n");
		//System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		//System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	}
	private int rand(int min, int max)
	{
		Random random = new Random();
		return random.nextInt(max - min + 1) + min;
	}
}

