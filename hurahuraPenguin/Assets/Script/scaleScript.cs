using UnityEngine;
using System.Collections;

public class scaleScript : MonoBehaviour {

	public CreatePrefabScript CPS;
	public GameObject CPSobject;
	BoxCollider bc;

	//Prefab create
	public GameObject Ice;

	//Scale set
	public float Scale_x = 2.0f;
	public float Scale_y = 2.0f;
	public float old_Scale_x;
	public float old_Scale_y;



	public bool touchFlag = false;

	// Use this for initialization
	void Start () 
	{
		CPSobject = GameObject.Find ("GameObject");
		CPS = CPSobject.GetComponent<CreatePrefabScript>();

		old_Scale_x = 2.0f;
		old_Scale_y = 3.0f;
	}
	
	// Update is called once per frame
	void Update () 
	{
		Ice = GameObject.Find ("iceBlock" + (CPS.number - 1).ToString());
		bc = Ice.GetComponent<BoxCollider> ();
		if (Input.GetMouseButton (0)) 
		{

			Ray ray = new Ray();
			RaycastHit hit = new RaycastHit();
			ray = Camera.main.ScreenPointToRay(Input.mousePosition);


			if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity))
			{
				//Debug.Log(hit.collider.gameObject.name);

				if (hit.collider.gameObject == Ice)
				{
					touchFlag = true;				
				}

			}

		}

		Ice.transform.localScale = new Vector3 (old_Scale_x, old_Scale_y,1);
		if (Input.GetMouseButtonUp (0)) 
		{
			touchFlag = false;
			Ice = null;
		}

		if (old_Scale_x >= 1.5f) 
		{
			bc.enabled = true;
		}

		if (old_Scale_x < 1.5f) 
		{
			bc.enabled = false;
		}

		if (touchFlag == true)
		{
			Scale_x += 0.025f;
			Scale_y += 0.025f;

			if (Scale_x >= 3.0f) 
			{
				Scale_x = 3.0f;
			}

			if (Scale_y >= 3.0f) 
			{
				Scale_y = 3.0f;
			}
			old_Scale_x = Scale_x;
			old_Scale_y = Scale_y;
		

		}else{
			Scale_x = 2.0f;
			Scale_y = 3.0f;

		}


	}


}
