package my.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class httpServletTest extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public httpServletTest() {
		super();
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		PrintWriter out=response.getWriter();
		Enumeration e=request.getHeaderNames();
		while(e.hasMoreElements())
		{
			String name=(String)e.nextElement();
			String value=request.getHeader(name);
			name="<font color=red>"+name+"<font>";
			out.println(name+"="+value);
			out.println("<br>");
		}
	}
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException
			{
			doGet(request,response);
		}
}
