using System.Linq;
using Windows.UI;
using Windows.UI.Xaml.Media;

namespace HLSL.Elements
{
    using rMind.Elements;
    
    using rMind.Content.Row;
    using rMind.Nodes;

    using Base;


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
		    return float4(input.color, 1.0f);
        };";

        const string DefaultTemplatePS = @"
        struct PixelShaderInput
        {{
            float3 color : COLOR0;
		}};

        float4 main(PixelShaderInput input) : SV_TARGET
		{{
            float4 color = {0};
		    return color;
        }};";

        public Material(rMindBaseController parent) : base(parent)
        {
            var row = new rMindRow
            {
                InputNode = new Node(this)
                {
                    NodeValueFormat = NodeValueFormat.FLOAT4,
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

        public string GetPixelShader()
        {
            if (m_nodes_link.ContainsKey("color")) {
                var node = m_nodes_link["color"];
                var reverseNode = node.GetReverseNodes().FirstOrDefault();
                var value = (reverseNode as Node)?.GetValue();

                if (!string.IsNullOrEmpty(value))
                {
                    return string.Format(DefaultTemplatePS, value);
                }                
            }
            return DefaultPS;
        }
    }
}
