#pragma once
#include "znoTouch_BaseOfPerformer.h"

#define TEXT_MAX 9

class TEXT :public BASE_OF_PERFORMER
{
private:

public:

	void Prepare() override;

	void Update() override;

	void Reset() override;
};

void InitTextT();
void UninitTextT();
void DrawTextT();
void UpdateTextT();

void AdjustText();
void ChangeBG();


void SetText(D3DXVECTOR2 position, int num);
TEXT* GetText();