﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class show : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        List<Book> a = (List<Book>)Session["book"];
        foreach (Book b in a)
        {
            Response.Write(b.name+"<BR>" );
        }
    }
}