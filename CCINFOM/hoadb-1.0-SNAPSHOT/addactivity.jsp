<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 8:53 pm
  To change this template use File | Settings | File Templates.
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.AssetActivity" %>
<%@ page import="com.example.hoadb.Asset" %>
<%@ page import="com.example.hoadb.Officer" %>

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

            String occupiedAssets = request.getParameter("assetdate");
            String ornum = request.getParameter("ornum");
            int officer_id = Integer.parseInt(request.getParameter("officer"));
            Officer o = new Officer();
            o.loadAssets();
            Officer o2 = new Officer();
            o2 = o.officers.get(officer_id);

            int officer = o2.ho_id;
            String officer_position = o2.position;
            String officer_edate = o2.election_date;

            Asset a = new Asset();
            a.loadAssets(true,
                "SELECT * FROM view_assets WHERE asset_id NOT IN ( SELECT asset_id FROM view_asset_transactions WHERE transaction_date LIKE \""+ occupiedAssets +"\");");%>
        <h2>Transaction Details</h2>
        Officer ID: <%=officer%> <br>
        Officer Position: <%=officer_position%> <br>
        Officer Election Date: <%=officer_edate%> <br>
        Transaction Type: A - Activity

        <h2>Asset Activity Details</h2>
        <form name = "addactivity2" action = "addactivity2.jsp" method ="POST">
            <input type="hidden" name="ornum" id="ornum" value =<%=ornum%>>
            <input type='hidden' name='officer_id' id = 'officer_id' value=<%=officer%>>
            <input type='hidden' name='officer_position' id = 'officer_position' value=<%=officer_position%>>
            <input type='hidden' name='officer_edate' id = 'officer_edate' value=<%=officer_edate%>>

            Available Assets:
            <select name = "available" id = "available">
                <%
                    for (int i=0; i < a.assets.size(); i++){
                        Asset e = new Asset();
                        e = a.assets.get(i);
                %>
                <option value = "<%=e.asset_id%>"> <%=e.asset_id%> - <%=e.asset_name%></option>
                <% } %>

            </select><br><br>
            <input type = "hidden" name = "assetdate" id = "assetdate" value = <%=occupiedAssets%>>
            Activity Description: <input type ="text" name = "description" id = "description"><br><br>
            Tentative Start:
            <input type="date" id = "tentative-start" name = "tentative-start"><br><br>
            Tentative End:
            <input type="date" id = "tentative-end" name = "tentative-end"><br><br>
            Actual Start:
            <input type="date" id = "activity-start" name = "activity-start"><br><br>
            Actual End:
            <input type="date" id = "activity-end" name = "activity-end"><br><br>
            Activity Cost: <input type="number" step="0.01" name = "cost" id="cost" value="0.00" placeholder="₱0.00" required><br><br>
            Status:
            <select name="status" id = "status" required>
                <option value = "S">Scheduled</option>
                <option value = "O">Ongoing</option>
                <option value = "C">Completed</option>
            </select> <br><br>
            <input type="submit" value="Submit" name="addactivity2" />
        </form>



    </body>
</html>
