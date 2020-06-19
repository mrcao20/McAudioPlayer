/* JSONListModel - a QML ListModel with JSON and JSONPath support
 *
 * Copyright (c) 2012 Romain Pokrzywka (KDAB) (romain@kdab.com)
 * Licensed under the MIT licence (http://opensource.org/licenses/mit-license.php)
 */

import QtQuick 2.12
import "jsonpath.js" as JSONPath

Item {
    property string source: ""
    property string json: ""
    property var jsonObject: null
    property string query: ""
    property var sort: null

    property ListModel model : ListModel { id: jsonModel }
    property alias count: jsonModel.count

    onSourceChanged: {
        var xhr = new XMLHttpRequest;
        xhr.open("GET", source);
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE)
                json = xhr.responseText;
        }
        xhr.send();
    }

    onJsonChanged: updateJSONModel()
    onJsonObjectChanged: updateJSONModel()
    onQueryChanged: updateJSONModel()
    onSortChanged: updateJSONModel()

    function updateJSONModel() {
        jsonModel.clear();

        if ( json === "" && jsonObject === null)
            return;
        if(jsonObject === null)
            jsonObject = JSON.parse(json);

        var objectArray = parseJSONObject(jsonObject, query);

        if(sort == null)
            modelSort(objectArray);
        else{
            for(var key in sort){
                var arr = sort[key];
                for(var value of arr){
                    modelSort(objectArray, key, value);
                }
            }
        }
    }

    function parseJSONObject(objectArray, jsonPathQuery) {
        if ( jsonPathQuery !== "" )
            objectArray = JSONPath.jsonPath(objectArray, jsonPathQuery);

        return objectArray;
    }

    function modelSort(objArr, key, value){
        for(var i = 0; i < objArr.length; ++i){
            var jo = objArr[i];
            if(key === undefined || value === undefined)
                jsonModel.append( jo );
            else if(jo[key] === value){
                jsonModel.append( jo );
                objArr.splice(i, 1);
                --i;
            }
        }
    }

}
