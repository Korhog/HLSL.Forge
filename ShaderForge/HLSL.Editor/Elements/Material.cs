using System.Linq;
using Windows.UI;
using Windows.UI.Xaml.Media;

namespace HLSL.Elements
{
    using rMind.Elements;
    
    using rMind.Content.Row;
    using rMind.Nodes;

    using Base;
    using HLSL.Values;


    /// <summary>
    /// HLSL Material 
    /// </summary>
    public class Material : HeaderRowContainerBase
    {

        const string DefaultPS = @"
        struct PixelShaderInput
        {
            float3 color : COLOR0;
		};

        float4 main(PixelShaderInput input) : SV_TARGET
		{
		    return float4(1.0f, 0.0f, 1.0f, 1.0f);
        };";

        const string DefaultTemplatePS = @"
        struct PixelShaderInput
        {{	
	        float4 pos : SV_POSITION;
	        float4 world : POSITION;	
	        float3 normal: NORMAL;
	        float3 color : COLOR0;
        }};

        float4 main(PixelShaderInput input) : SV_TARGET
		{{
            {0}

            float4 color = {1};

		    return color;
        }};";

        public Material(rMindBaseController parent) : base(parent)
        {
            var row = new rMindRow
            {
                InputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT4,
                    IDS = "color",
                    Label = "Color",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Left,
                    Stroke = new SolidColorBrush(Colors.White)
                },
                OutputNodeType = rMindNodeConnectionType.None
            };

            AddRow(row);            
        }

        /// <summary>
        /// Инициализируем всякие переменные
        /// </summary>
        string GetPSDefine()
        {
            var definers = Parent.Items
                .Where(x => x is IHLSLRequireDefine)
                .GroupBy(x => x.GetType().Name)
                .Select(g => g.FirstOrDefault() as IHLSLRequireDefine)
                .Select(x => x.GetDefineCode())
                .ToArray();

            return string.Join("\n", definers);
        }

        public string GetPixelShader()
        {
            if (m_nodes_link.ContainsKey("color")) {
                var node = m_nodes_link["color"] as Node;
                var reverseNode = node.GetReverseNodes().FirstOrDefault() as Node;

                if (reverseNode == null)
                    return DefaultPS;

                var value = reverseNode.GetValue();


                string color;
                if (node.HLSLValueBaseType == value.HLSLValueBaseType)
                {
                    color = value.Value;
                }
                else
                {
                    color = HLSL.Converter.HLSLValueConverterContainer.Current().Convert(
                        value,
                        new HLSLValue { HLSLValueBaseType = node.HLSLValueBaseType }
                    );
                }
                var init = GetPSDefine();



                if (!string.IsNullOrEmpty(color))
                { 
                    return string.Format(DefaultTemplatePS, init, color);
                }                
            }
            return DefaultPS;
        }
    }
}
