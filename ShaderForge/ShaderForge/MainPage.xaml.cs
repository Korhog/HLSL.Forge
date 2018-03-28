using Windows.UI;
using Windows.UI.Xaml.Controls;

namespace ShaderForge
{
    using rMind.CanvasEx;
    using rMind.Elements;
    using rMind.Content;
    using rMind.Nodes;

    using HLSL.Elements;
    using System;

    public sealed partial class MainPage : Page
    {
        rMindCanvasController canvasController;
        rMindBaseController rootController;

        public MainPage()
        {
            this.InitializeComponent();

            canvasController = new rMindCanvasController(canvas, scroll);
            rootController = new rMindBaseController(canvasController);

            canvasController.SetController(rootController);
            CreateMaterialNode();

            canvasController.Draw();
            dx.StartRenderLoop();
        }

        void CreateMaterialNode()
        {
            var material = new Material(rootController)
            {
                Header = "Material",
                CanEdit = false
            };
            rootController.AddElement(material);

            rootController.AddElement(new ColorNode(rootController)
            {
                Header = "Color node",
                CanEdit = true
            });
        }

        private void OnAdd(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            rootController.AddElement(new MathNodeBase(rootController));
           
        }

        private void OnCompile(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {  
            try
            {
                dx.CompilePixelShader("");
            }
            catch(Exception ex)
            {
                var l = ex.Message;
            }
            
        }
    }
}
