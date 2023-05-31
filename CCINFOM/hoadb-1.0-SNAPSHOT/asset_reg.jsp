<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.Asset" %>

<html>
    <head>
        <link rel="stylesheet" href="style.css">
        <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
        <title>Asset Registration Form</title>
    </head>

    <body>
        <h1>Asset Registration Form</h1>
        <jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />
        <%assetBean.loadAssets("type_asset LIKE \"P\""); %>
        <%assetBean.loadHOAName(); %>
        <!-- Method to load assets here -->

        <form name = "registerasset" action="addasset.jsp" method = "POST">
            Asset Name: <input type="text" name = "name" id = "name" required><br><br>
            Asset Description: <input type="text" name = "desc" id = "desc" required> <br><br>
            Acquisition Date: <input type="date" name = "acqdate" id = "acqdate" required> <br><br>
            Rentable: <input type = "checkbox" name="yesOption" value = "yes" >
                      <label for="yesOption">Yes</label><br>
            Asset Value: <input type="number" step="0.01" name = "assetvalue" id="assetvalue" value="0.00" placeholder="₱0.00" required> <br><br>
            Type of Asset:
            <select name="types" id = "types" required>
            <option value = "P">P - Property</option>
                <option value = "E">E - Equipment</option>
                <option value = "F">F - Furniture</option>
                <option value = "O">O - Others</option>
            </select>
            <br><br>
            Status of Asset:
            <select name="status" id = "status" required>
                <option value = "W">W - Working Condition</option>
                <option value = "D">D- Deteriorated</option>
                <option value = "P">P - For Repair</option>
                <option value = "S">S - For Disposal</option>
            </select> <br><br>
            Current Location: <input type="number" name="curLocationX" id="curLocationX" value="0.0" placeholder="0.0" required>
                              <input type="number" name="curLocationY" id="curLocationY" value="0.0" placeholder="0.0" required><br><br>
            HOA:
            <select name ="HOA" id = "HOA" required>
                    <%
                        System.out.println("DETECTING: " + assetBean.hoa_names.size());
                        for (int i = 0; i < assetBean.hoa_names.size(); i++) {
                            String a = new String();
                            a = assetBean.hoa_names.get(i);
                            System.out.println(a);%>
                <option value = "<%=a%>"><%=a%></option>
                    <% }%>
            </select> <br><br>
            Enclosing Asset:
                <select name ="parentid" id = "parentid">
                    <option value = "none"> None </option>
                    <%
                        System.out.println("DETECTING: " + assetBean.assets.size());
                        for (int i = 0; i < assetBean.assets.size(); i++) {
                            Asset a = new Asset();
                            a = assetBean.assets.get(i);
                            System.out.println(a.asset_id);%>
                            <option value = "<%=a.asset_id%>"> <%=a.asset_id%> - <%=a.asset_name%></option>
                    <% }%>


                </select><br><br>
            <input type="submit" value="Add Asset" name="Add Asset" />
        </form>
    </body>
</html>
