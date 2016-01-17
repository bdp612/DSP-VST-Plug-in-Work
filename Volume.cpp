bool __stdcall CVolume::processAudioFrame(float* pInputBuffer, float* pOutputBuffer, UINT uNumInputChannels, UINT uNumOutputChannels)
{
	// output = input -- change this for meaningful processing
	//
	// Do LEFT (MONO) Channel; there is always at least one input/one output
	// (INSERT Effect)
	pOutputBuffer[0] = pInputBuffer[0] * m_fVolume;

	// Mono-In, Stereo-Out (AUX Effect)
	if(uNumInputChannels == 1 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[0] * m_fVolume;;

	// Stereo-In, Stereo-Out (INSERT Effect)
	if(uNumInputChannels == 2 && uNumOutputChannels == 2)
		pOutputBuffer[1] = pInputBuffer[1] * m_fVolume;;


	return true;
}
