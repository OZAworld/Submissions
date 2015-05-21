using UnityEngine;
using System.Collections;


public class penpenDeath : MonoBehaviour {
	public GameObject oboPen;
	public GameObject killer;
	public GameObject Dead;



	public void oboPen_create()
	{
		Instantiate (oboPen, transform.position, transform.rotation);
	}

	public void oboPen_destroy()
	{
		Destroy (oboPen);
	}

	public void killer_create()
	{
		Instantiate (killer, transform.position, transform.rotation);
	}

	public void gameover()
	{
		audio.Play ();
		Instantiate (Dead, transform.position, transform.rotation);
	}
}
