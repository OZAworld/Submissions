using UnityEngine;
using System.Collections;



public class CreatePrefabScript : MonoBehaviour {

	//Prefab create
	public GameObject Ice;
	//Click position
	private Vector3 clickPosition;
	public int number;

	public bool createFlag;

	public gameEvent gameevent;

	// Use this for initialization
	void Start () 
	{
		gameevent = GetComponent<gameEvent> ();
		gameevent.gameFlag = true;
		number = 0;
	}
	
	// Update is called once per frame
	void Update () {


		if (Input.GetMouseButtonDown (0))
		{
			clickPosition = Input.mousePosition;
			//Z cure
			clickPosition.z = 11.0f;
			if (number < 20) 
			{
				createFlag = true;
			}
			if (createFlag == true) 
			{
				var obj = Instantiate (Ice, Camera.main.ScreenToWorldPoint (clickPosition), Ice.transform.rotation);
				obj.name = Ice.name + number.ToString ();
				number++;
			}
			if (number >= 20) 
			{
				createFlag = false;
			}
		}
	

	}
}
