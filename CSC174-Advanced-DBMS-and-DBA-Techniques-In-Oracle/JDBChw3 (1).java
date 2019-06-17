import java.sql.*;

public class JDBChw3

{

  public void displayData(String urlStr,String username,String password)
  {

		  try
		  {

			  DriverManager.registerDriver (new oracle.jdbc.driver.OracleDriver());
			  Connection conn = DriverManager.getConnection(urlStr,username,password);
			  System.out.println ("Connected to the Oracle database");


			  Statement stmt1 = conn.createStatement();
			  ResultSet rs1=null;
			  rs1=stmt1.executeQuery("select * from art_object, sculpture WHERE art_object.id_no = sculpture.id_no AND material = 'Marble'");
			  System.out.println ("Querying DB for all sculptures made of Marble.");
			  while (rs1.next())
			  {
				  System.out.print("Sculpture Name: "+rs1.getString(3));
				  System.out.print("  *  Date Created: "+rs1.getString(2));
				  System.out.println("  *    Made by: " +rs1.getString(5));
			  }
			//  stmt1.close();

			  Statement stmt2 = conn.createStatement();
			  ResultSet rs2=null;
			  rs2=stmt1.executeQuery("select * from painting_exhibition");
			  System.out.println ("\n\n\nQuerying DB for the Painting Exhibition view");
			  while (rs2.next())
		  	  {
				System.out.print("Exhibition Name: " + rs2.getString(1));
				System.out.print("   *   Title of Painting: " + rs2.getString(2));
				System.out.println("   *   Style: " + rs2.getString(3));
			  }
			  stmt2.close();
		
			  CallableStatement cstmt = conn.prepareCall("{?= call num_of_sculpture(?)}"); //call a function
			  cstmt.registerOutParameter(1,Types.NUMERIC);
			  cstmt.setString(2,"E3");
			  cstmt.execute();
			  System.out.println ("\n\n\nNumber of sculptures in E3 is "+ cstmt.getBigDecimal(1).toString());
			  cstmt.close();

			  conn.close();


		  }
		  catch (Exception e)
		  {
			  e.printStackTrace();
		  }

  }

  public static void main (String args [])
  {
		String url= "jdbc:oracle:thin:@eagle.ecs.csus.edu:1521:eagle";
		String username= "cs174128";
		String password = "union678";

		JDBChw3 example = new JDBChw3();
		example.displayData(url,username,password);

  }

}

