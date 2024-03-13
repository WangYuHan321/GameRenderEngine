#version 420 core
struct AtmosphereParameter
{
	float SeaLevel;
	float PlanetRadius;//行星半径
	float AtmosphereHeight;
	float SunLightIntensity;
	float SunLightColor;
	float SunDiskAngle;
	float RayleighScatteringScale;
	float RayleighScatteringScalarHeight;// 默认为8500 是用来拟合该类型散射的高度衰减曲线的系数，也称为标高（scalar height）
	float MieScatteringScale;
	float MieAnisotropy; //米氏散射，相位函数一个各向异性项 g，它介于 [-1,1] 之间，用来控制米氏散射波瓣的形状。也是控制日晕大小的参数
	float MieScatteringScalarHeight;// 默认为1200 是用来拟合该类型散射的高度衰减曲线的系数，也称为标高（scalar height）
	//臭氧层是一个特定高度的层
	float OzoneAbsorptionScale;
	float OzoneLevelCenterHeight;//中心高度 一般 25km
	float OzoneLevelWidth;//厚度 一般15km
}

// By WangYuHan 2023 06.21

// 在这里 瑞利和米氏 σ（λ，0）为一个标准测量单位
// 由于 空气这种介质，它的密度通常随着海拔的增高而降低
// 因此可以用海平面（Y=0）处的散射系数和海平面 h 处的高度密度衰减函数 p(h) 来描述任意高度的散射系数：

//phase(Θ) 相位函数 表述了反弹后剩下的能量有多少能够逃到指定的方向上

//瑞利散射
// σ（λ，0） =  （5.802， 13.558， 33.1） * 10 ^ -6
// phase(Θ) = 3 / 16Π * （1 + cos ^ 2 Θ）
// p(h) = exp(-h / H), H = 8500

// σ（λ，h）= σ（λ，0）* p(h) --> 转换到对应海拔高度 的空气密度散射系数

float3 RayleighCoefficient(AtmosphereParameter param, float h)
{
	const float3 sigma = float3(5.802, 13.558, 33.1) * 1e-6;
	const H_R = param.RayleighScatteringScalarHeight;	
	float rho_h = exp(-(h / H_R));
	return sigma * rho_h;
}

float RayleiPhase(AtmosphereParameter param, float cos_theta)
{
	return (3.0 / (16.0 * PI)) * (1.0 + cos_theta * cos_theta);
}

//米氏散射
// σ（λ，0） =  （3.996， 3.996， 3.996） * 10 ^ -6
// phase(Θ) = 3 / 8Π * （1 - g^2) / (2 + g^2) * 1 + cos ^ 2 Θ / (1 + g^2 - 2g*cosΘ) ^ 3/2
// // p(h) = exp(-h / H), H = 1200

// σ（λ，h）= σ（λ，0）* p(h) --> 转换到对应海拔高度 的空气密度散射系数

float3 MieCoefficient(AtmosphereParameter param, float h)
{
	const float3 sigma = float3(3.996) * 1e-6;
	const H_R = param.MieScatteringScalarHeight;
	float rho_h = exp(-(h / H_R));
	return sigma * rho_h;
}

float MiePhase(AtmosphereParameter param, float cos_theta)
{	
	float g = param.MieAnisotropy;
	
	float a = 3.0 / (8.0 * PI);
	float b = (1.0 - g * g) / (2.0 + g * g);
	float c = 1.0 + cos_theta * cos_theta;
	float d = pow(1 + g * g - 2 * g * cos_theta, 1.5);
	
	return a * b * (c / d);	
}

// 透射函数
//σt = σs + σa
//瑞利散射不会发生吸收 米氏 σa = (4.40, 4.40, 4.40) * 10 ^ -6 臭氧 σa = (0.650, 1.881, 0.085) * 10 ^ -6 
//米氏 吸收和p（h）一样 臭氧 p（h） = max(0, 1- |h - center| / width)

float3 MieAbsorption(AtmosphereParameter param, float h)
{
	const float3 sigma = float3(4.4) * 1e-6;
	float H_M = param.MieScatteringScalarHeight;
	float rho_h = exp(- (h / H_M));
	return sigma * rho_h;
}

float3 OzoneAbsorption(AtmosphereParameter param, float h)
{
	#define sigma_lambda (float3(0.650, 1.881, 0.085)) * 1e-6
	float center = param.OzoneLevelCenterHeight;
	float width = param.OzoneLevelWidth;
	float rho = max(0, 1.0 - (abs(h - center) / width));
	return sigma_lambda * rho;
}

float OzoneAbsorption(AtmosphereParameter param, float h)
{
	const float3 sigma = float3(4.4) * 1e-6;
	float H_M = param.MieScatteringScalarHeight;
	float rho_h = exp(- (h / H_M));
	return sigma * rho_h;
}

//散射 = 瑞利 * phase + 米氏 * phase
// p为当前积分中的一点 inDir 为光照向量 outDir为相机视角向量
float3 Scattering(AtmosphereParameter param, float3 p, float3 inDir, float3 outDir)
{
	float cos_theta = dot(inDir, outDir);
	
	//当前海拔高度可以用当前坐标的模长减去行星半径得到
	float h = length(p) - param.PlanetRadius;
	//当前散射系数 * 相位函数
	float3 rayleigh = RayleighCoefficient(param, h) * RayleiPhase(param, cos_theta); 
	float3 mie = MieCoefficient(param, h) * MiePhase(param, cos_theta);
	
	return rayleigh + mie;
}

//积分 p2 - p1 p1为空气中一点
float3 Transmittance(AtmosphereParameter param, float3 p1, float3 p2)
{
	
}