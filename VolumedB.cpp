bool __stdcall CVolumedB::userInterfaceChange(int nControlIndex)
{
	// decode the control index, or delete the switch and use brute force calls
	switch (nControlIndex)
	{
	case 0:
	{
		// Cook the raw data:
		m_fVolume = pow(10.0, m_fVolume_dB / 20.0);
	}

	default:
		break;
	}

	return true;
}

bool __stdcall CVolumedB::processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels)
{
	// output = input -- change this for meaningful processing
	//
	// Do LEFT (MONO) Channel; there is always at least one input/one output
	// (INSERT Effect)
	pOutputBuffer[0] = pInputBuffer[0] * m_fVolume;

	// Mono-In, Stereo-Out (AUX Effect)
	if (uNumInputChannels == 1 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[0] * m_fVolume;

	// Stereo-In, Stereo-Out (INSERT Effect)
	if (uNumInputChannels == 2 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[1] * m_fVolume;


	return true;
}
