package com.bbque.android.service;

/**
 * System-private API for talking to the BbqueService.
 *
 * {@hide}
 */
interface IBbqueService {
	int getNumCore();
	int getMoreCore();
	int getLessCore();
	int freeCore();
	int sendMessageToApp();
}
