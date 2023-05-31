<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 15/04/2023
  Time: 12:27 am
  To change this template use File | Settings | File Templates.
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.AssetActivity" %>
<%@ page import="com.example.hoadb.Asset" %>
<%@ page import="com.example.hoadb.Transaction" %>

<html>
    <head>
        <link rel="stylesheet" href="style.css">
        <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
        <title>Asset Activity Registration Form</title>
    </head>
    <body>
        <h1>Asset Registration Form</h1>
        <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />
        <%
            //transaction details
            Transaction t = new Transaction();

            t.asset_id = Integer.parseInt(request.getParameter("available"));
            t.transaction_date = request.getParameter("assetdate");
            t.trans_hoid = Integer.parseInt(request.getParameter("officer_id"));
            t.trans_position = request.getParameter("officer_position");
            t.trans_electiondate = request.getParameter("officer_edate");
            t.ornum = Integer.parseInt(request.getParameter("ornum"));
            t.addRecord(); //there is now a transaction for


            //asset activity information
            activityBean.failed = false;
            activityBean.activity_date = request.getParameter("assetdate");
            activityBean.asset_id = Integer.parseInt(request.getParameter("available"));
            activityBean.activity_description = request.getParameter("description");
            activityBean.tent_start = request.getParameter("tentative-start");
            activityBean.tent_end = request.getParameter("tentative-end");
            activityBean.act_start = request.getParameter("activity-start");
            activityBean.act_end = request.getParameter("activity-end");
            activityBean.status = request.getParameter("status");
            activityBean.cost = Double.parseDouble(request.getParameter("cost"));
            activityBean.addActivity();

            if (!activityBean.failed)
            {%>
            Transaction record added. <br>
            Transaction Details: <br>
            Asset ID: <%=t.asset_id%><br>
            Asset Transaction Date: <%=t.transaction_date%> <br>
            Transaction Approved By Officer ID <%=t.trans_hoid%><br>
            Officer Position: <%=t.trans_position%><br>
            Officer Election Date: <%=t.trans_electiondate%><br>
            Transaction OR number: <%=t.ornum%><br>
            Transaction Type: A - Activity <br><br>
        <% } else { %>
            <h3 style="color:red"> Error Adding Activity </h3>
            Reason: <%=activityBean.errorMessage%> <br><br>

        <% }%>






        Click <a href="index.jsp">here to go back to main menu</a><br>
    </body>
</html>
