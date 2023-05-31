<%@ page import="com.example.hoadb.Asset" %><%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 2:17 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
    <title>Update Asset Form</title>
</head>
<body>
<h1>Update Asset Form</h1>
<jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />



<form name = "updateAsset" action="updateasset.jsp" method = "POST">
    <%
        assetBean.failed = false;
        assetBean.loadAssets();
        int index = 0;
        if (!request.getParameter("assetindex").equals("none"))
        {
            index = Integer.parseInt(request.getParameter("assetindex"));
            assetBean = assetBean.getAsset(index);
            assetBean.loadAssets("asset_id != " + assetBean.asset_id + " AND type_asset = 'P'");
            assetBean.asset_index = index;
            assetBean.loadHOAName(); %>
            Asset Name: <%=assetBean.asset_name%><br><br>
            Asset Description: <%=assetBean.asset_description%> <br><br>
            Acquisition Date: <%=assetBean.acquisition_date%> <br><br>
            Asset Value: <%=assetBean.asset_value%><br><br>
            Asset Type: <%=assetBean.typeString()%><br><br>
            HOA: <%=assetBean.hoa_name%><br><br>

            Rentable: <input type = "checkbox" name="yesOption" value = "yes">
            <label for="yesOption">Yes</label><br>
            <br><br>
            Status of Asset:
            <select name="status" id = "status" required>
                <option value = "W">W - Working Condition</option>
                <option value = "D">D- Deteriorated</option>
                <option value = "P">P - For Repair</option>
                <option value = "S">S - For Disposal</option>
            </select> <br><br>
            Current Location: <input type="number" name="curLocationX" id="curLocationX" value="0" required>
            <input type="number" name="curLocationY" id="curLocationY" value="0" required><br><br>
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
            <input type="hidden" name="index" id = "index" value=<%=assetBean.asset_index%> />
            <input type="submit" value="Submit" name="Submit" />
    <% } else {%>
        No Asset Selected.<br><br>
        click <a href="index.jsp">here to go back to Main Menu</a><br>
    <%}%>


</form>


</body>
</html>
