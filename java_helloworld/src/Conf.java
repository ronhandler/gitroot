import java.net.URLDecoder;
import java.nio.file.*;
import java.io.IOException;
import java.util.Properties;
import java.io.FileInputStream;

class Conf
{
	protected Properties prop;

	public static String getBinDir()
	{
		String path;
		String decodedPath;
		try {
			path = Main.class.getProtectionDomain().getCodeSource().getLocation().getPath();
			Path tmppath = Paths.get(URLDecoder.decode(path, "UTF-8"));
			decodedPath = tmppath.getParent().toString();
		} catch(IOException e) {
			e.printStackTrace();
			decodedPath="";
		}
		return decodedPath;
	}
	public boolean loadConfig(String str)
	{
		String propFileName;
		if (str.startsWith(".")) {
			propFileName = getBinDir() + "/" + str;
		} else {
			propFileName = str;
		}

		prop = new Properties();

		try {
		  prop.load(new FileInputStream(propFileName));
		} catch (IOException e) {
			//e.printStackTrace();
			System.err.println("Conf::loadConfig error: " + e.toString());
			System.exit(1);
		}
		return true;
	}
	public String getVal(String str)
	{
		return prop.getProperty(str);
	}
}
