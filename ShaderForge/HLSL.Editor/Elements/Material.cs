using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Elements
{
    using rMind.Elements;
    using rMind.Content.Row;
    using rMind.Nodes;
    using Windows.UI.Xaml.Media;
    using Windows.UI;

    /// <summary>
    /// HLSL Material 
    /// </summary>
    public class Material : HeaderRowContainerBase
    {
        public Material(rMindBaseController parent) : base(parent)
        {
            var row = new rMindRow
            {
                InputNode = new rMindBaseNode(this)
                {
                    Label = "Color",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Left,
                    Stroke = new SolidColorBrush(Colors.White)
                },
                OutputNodeType = rMindNodeConnectionType.None
            };

            AddRow(row);
        }
    }
}
