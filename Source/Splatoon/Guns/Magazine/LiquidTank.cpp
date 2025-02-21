#include "LiquidTank.h"

void ULiquidTank::Init(UMaterialInstanceDynamic* Material)
{
	LiquidMaterial = Material;
}

void ULiquidTank::SetPercent(float Percent)
{
	if (LiquidMaterial)
	{
		LiquidMaterial->SetScalarParameterValue(FName("BulletCount"), Percent);
	}
}
