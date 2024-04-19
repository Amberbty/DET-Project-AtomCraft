using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using NativeWebSocket;
using System.Runtime.CompilerServices;

public class WebSocketClient : MonoBehaviour
{
    [SerializeField]
	private string IPAdress = "10.204.0.122"; //The IP Adress of the Server you want to connect to
    [SerializeField]
	private int Port = 7890; //The Port your WebSocket Connection will "talk" to
    
	private WebSocket webSocket;

	private void initWebSocket() //Starts WebSocket Client Connection
	{
		webSocket = new WebSocket($"ws://{IPAdress}:{Port}");
		webSocket.Connect();

		webSocket.OnOpen += WebSocket_OnOpen;
		webSocket.OnError += WebSocket_OnError;
		webSocket.OnClose += WebSocket_OnClose;
		webSocket.OnMessage += WebSocket_OnMessage;

	}

	private void WebSocket_OnOpen() //Alerts on console when WebSocket Connection is Successfull
	{
		Debug.Log("Connecion opened!");
	}

	private void WebSocket_OnError(string error) //Alerts on console when WebSocket Connection is Unsuccessfull
	{
		Debug.Log($"Error: {error}");
	}

	private void WebSocket_OnClose(WebSocketCloseCode closeCode) //Alerts on console when WebSocket Connection is Closed
	{
		Debug.Log("Connection closed!");
	}

	private void WebSocket_OnMessage(byte[] data) //Receives webSocket message and handles it respectively depending on what it contains
	{
		string socketMessage = System.Text.Encoding.UTF8.GetString(data);
		//Debug.Log(System.Text.Encoding.UTF8.GetString(data));
        Debug.Log(socketMessage);
        
	}
	
	
		
	public async void SendWebSocketMessage(string text) //Sends Websocket Message to Server for the ESP32 to receive
	{

		Debug.Log("Sending message to server: " + text);

		if (webSocket.State == WebSocketState.Open)
		{
			// Sending plain text socket
			await webSocket.SendText(text);
		}
	}
	

	// Start is called before the first frame update
	void Start()
	{
		initWebSocket();
		Debug.Log("Started");
	}

	// Update is called once per frame
	async void Update()
	{
		webSocket.DispatchMessageQueue();
		if(Input.GetKeyDown(KeyCode.Space)){
			SendWebSocketMessage("Pressed Space");
		}

    }
	

	private async void OnApplicationQuit() //Closes Websocket Connection Correctly when app is closed
	{
		await webSocket.Close();
	}


	
}


