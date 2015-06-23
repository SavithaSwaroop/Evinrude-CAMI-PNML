import java.io.*;
public class Grap {
    public static void main(String args[]) {
        try {
			File file = new File(args[0]);
            BufferedReader fr = new BufferedReader(new FileReader(file));
            FileWriter fw = new FileWriter(args[1]);
			String line;
			int x=200,i=1,y1,y2;
            while((line = fr.readLine()) != null && line.length()!=0)
			{
			if(i%3==0)
				{
				y1=200;
				y2=400;
				}
			else
				{
				y1=150;
				y2=350;
				}
				i++;
			if (line.startsWith("<pnml"))
			{
				System.out.println(line+"1\n");
				fw.write("<pnml>\n");
				continue;
			}
			if (line.contains("<place"))
				{					
				System.out.println(line);
				fw.write(line+"2\n");
				fw.write("<graphics> \n");
				fw.write("<position x='"+x+"' y='"+y1+"' /> \n");
				fw.write("</graphics> \n");
				x+=90;
				continue;
				}
			else if (line.contains("<transition"))
				{
				System.out.println(line);
				fw.write(line+"3\n");
				fw.write("<graphics> \n");
				fw.write("<position x='"+x+"' y='"+y2+"' /> \n");
				fw.write("</graphics> \n");
				x+=40;
				continue;
				}
	        else
				{
				fw.write(line+"\n");
				System.out.println(line);
				continue;
				}
            }
			fr.close();
			fw.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
	}